import json
import time
import paho.mqtt.client as mqtt
import pandas as pd
import matplotlib.pyplot as plt

BROKER = "broker.hivemq.com"
PORT = 1883
TOPIC = "unsoed/tk245004/kelompok3/data"  # Sesuaikan dengan topic ESP32
JUMLAH_SAMPEL = 30

data = []

def on_connect(client, userdata, flags, reason_code, properties):
    print("Terhubung ke broker, kode:", reason_code)
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    try:
        payload = json.loads(msg.payload.decode())
        suhu = float(payload["suhu"])
    except (ValueError, KeyError):
        print("Data tidak valid, diabaikan")
        return

    data.append({
        "waktu": time.strftime("%Y-%m-%d %H:%M:%S"),
        "suhu": suhu
    })
    print(f"[{len(data)}/{JUMLAH_SAMPEL}] suhu = {suhu}")

    if len(data) >= JUMLAH_SAMPEL:
        client.disconnect()

# Tahap 1: Akuisisi data dari MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER, PORT)
client.loop_forever()

# Tahap 2: Simpan data ke CSV
df = pd.DataFrame(data)
df.to_csv("data_suhu.csv", index=False)
print("Data tersimpan di data_suhu.csv")

# --- Tahap 3: Hitung Moving Average (Jendela 5) ---
# Menghitung rata-rata bergerak dengan jendela 5 data
df["suhu_ma"] = df["suhu"].rolling(window=5).mean()
# Mengisi nilai NaN di awal (karena 4 data pertama tidak punya 5 data sebelumnya) dengan nilai suhu asli
df["suhu_ma"] = df["suhu_ma"].fillna(df["suhu"])

# --- Tahap 4: Analisis statistik dan deteksi anomali pada data MA ---
rata2_ma = df["suhu_ma"].mean()
std_ma = df["suhu_ma"].std()

if std_ma == 0:
    df["zscore"] = 0.0
else:
    df["zscore"] = (df["suhu_ma"] - rata2_ma) / std_ma

df["anomali"] = df["zscore"].abs() > 2

print(f"Rata-rata : {rata2_ma:.2f}")
print(f"Std deviasi: {std_ma:.2f}")
print(f"Minimum   : {df['suhu'].min():.2f}")
print(f"Maksimum  : {df['suhu'].max():.2f}")
print(f"Jumlah anomali setelah Moving Average: {df['anomali'].sum()}")

# Tahap 5: Visualisasi
plt.figure(figsize=(10, 4))
plt.plot(df.index, df["suhu"], marker="o", label="Suhu")

# Plot juga data Moving Average
plt.plot(df.index, df["suhu_ma"], marker=".", linestyle="--",
         label="Moving Average", alpha=0.7)

anom = df[df["anomali"]]
plt.scatter(
    anom.index,
    anom["suhu"],
    color="red",
    s=100,
    label="Anomali",
    zorder=3
)

plt.axhline(rata2_ma, color="gray", linestyle="--", label="Rata-rata")
plt.xlabel("Urutan data")
plt.ylabel("Suhu (°C)")
plt.title("Data Suhu dan Deteksi Anomali")
plt.legend()
plt.tight_layout()
plt.savefig("grafik_suhu.png")
plt.show()
