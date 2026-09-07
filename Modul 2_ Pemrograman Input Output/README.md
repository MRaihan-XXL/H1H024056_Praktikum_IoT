<h2>Menghidupkan LED Dengan Pin GPIO Arduino</h2>
<p>Pada kegiatan pembelajaran pertama ini, kita akan menggunakan Arduino untuk menyalakan sebuah LED. Kita belum akan menulis kode apa pun. Tujuan utama kegiatan ini adalah untuk mulai mengenal perangkat keras Arduino serta cara menghubungkan komponen ke pin-pin Arduino. Pemrograman akan diperkenalkan pada pelajaran berikutnya.</p>

<img width="1536" height="632" alt="Turn on LED" src="https://github.com/user-attachments/assets/e15933d7-aeab-4216-9321-fa8cedb0e32d" />

<h3>Alat dan Bahan</h3>
<p>Dalam percobaan sederhana ini, berikut alat dan bahan yang digunakan:</p>

<div align="center">
<table border="1" cellpadding="10" cellspacing="0" width="100%">
  <tr>
    <th>Arduino</th>
    <th>LED</th>
    <th>Resistor</th>
    <th>Bradboard</th>
    <th>Jumper</th>
  </tr>

  <tr align="center">
    <td>
      <img width="333" height="236" alt="arduino_uno" src="https://github.com/user-attachments/assets/b5b0c26f-9547-421f-81d7-797fc487e10c" /><br>
    </td>
    <td>
      <img width="108" height="268" alt="RedLED_Fritzing" src="https://github.com/user-attachments/assets/a1726590-6b0c-49b8-ab84-96ff8e243ae2" /><br>
    </td>
    <td>
      <img width="224" height="65" alt="Resistor220_Fritzing" src="https://github.com/user-attachments/assets/b925fae3-2191-4f7e-96b1-796ea142c62f" /><br>
    </td>
    <td>
      <img width="500" height="326" alt="breadboard" src="https://github.com/user-attachments/assets/0d1b7929-81f3-4bb2-a0de-757ef79bc916" /><br>
    </td>
    <td>
      <img width="229" height="344,5" alt="pngwing com" src="https://github.com/user-attachments/assets/0acc9c70-b288-4152-864e-e7bc8372ad91" /><br>
    </td>
  </tr>

  <tr align="center">
    <td>Arduino Uno, Leonardo, atau lainnya</td>
    <td>Red LED</td>
    <td>220Ω Resistor atau lainnya</td>
    <td>Breadboard Mini</td>
    <td>Kabel Jumper</td>
  </tr>
</table>
</div>

https://github.com/user-attachments/assets/f7cdb8a6-88bf-4d08-8d53-e44660e340a3

<h1>Pengenalan GPIO</h1>
<p>GPIO (General Purpose Input/Output) adalah salah satu fitur penting dalam pengembangan proyek elektronik dan pemrograman mikrokontroler. Pada Arduino, fungsi GPIO memungkinkan pengguna untuk melakukan interaksi langsung dengan lingkungan sekitar, seperti membaca data dari sensor, mengoperasikan motor maupun menyalakan LED. GPIO adalah pin pada mikrokontroler atau komputer papan tunggal (seperti Raspberry Pi) yang dapat dikonfigurasi sebagai input atau output sesuai kebutuhan pengguna. Pin-pin ini tidak memiliki fungsi khusus bawaan, sehingga disebut "general purpose" (serbaguna).</p>

<p>Pada mikrokontroler Arduino berbasis ATmega, setiap pin secara default berada dalam mode input setelah sistem dinyalakan. Oleh karena itu, tidak selalu diperlukan pemanggilan fungsi pinMode() untuk menetapkannya sebagai input.</p>

<p>Pada tahap ini, kita mulai menyalakan LED menggunakan program dengan memberikan logika HIGH (5V) pada Pin 11. Selanjutnya, program tersebut akan diubah sehingga LED tidak hanya menyala terus, tetapi juga dapat berkedip. Untuk itu, kita perlu memahami konsep keluaran digital pada Arduino.</p>

<p>Arduino Uno memiliki 20 pin GPIO yang dapat digunakan untuk menerima atau mengirim sinyal digital, yaitu HIGH dan LOW. Sinyal ini dikendalikan melalui fungsi digitalRead() untuk membaca dan digitalWrite() untuk menulis nilai digital.</p>

<p>Walaupun pin digital lain juga bisa digunakan, Pin 11 dipilih agar konsisten dengan pelajaran selanjutnya, sehingga proses belajar menjadi lebih sederhana dan tidak membingungkan.</p>

<img width="2615" height="1338" alt="ArduinoUno_DigitalIOPins" src="https://github.com/user-attachments/assets/3371335e-856c-4e6e-bbf8-601be8211c1c" />

<p>Anda dapat mengendalikan salah satu dari 20 pin digital I/O tersebut dengan menggunakan tiga fungsi berikut:</p>
<ul>
  <li>pinMode(int pin, int mode). Fungsi ini digunakan untuk mengatur sebuah pin agar berfungsi sebagai INPUT atau OUTPUT. Dalam kasus ini, kita memilih OUTPUT karena kita ingin mengirimkan sinyal untuk menyalakan LED.</li>

<li>digitalRead(int pin). Fungsi ini digunakan untuk membaca sinyal digital dari pin tertentu, yaitu HIGH atau LOW. Fungsi digitalRead akan dibahas lebih lanjut pada seri pelajaran pengantar input.</li>

<li>digitalWrite(int pin, int value). Fungsi ini digunakan untuk mengirimkan sinyal digital ke pin tertentu, yaitu HIGH atau LOW. Pada pelajaran ini, kita akan menggunakan fungsi digitalWrite.</li>
</ul>

<h2>Bagaimana kita menghitung 20 pin I/O digital?</h2>
<p>Pada Arduino Uno dan Leonardo, tulisan dan label pada papan sering membuat kita mengira hanya ada 14 pin digital. Padahal, jika dilihat secara keseluruhan, terdapat 20 pin digital I/O yang bisa digunakan. Untuk memastikan hal ini, kita dapat melihat diagram pinout resmi Arduino Uno yang menunjukkan semua pin yang tersedia.</p>

<img width="2621" height="1418" alt="ArduinoUno_OfficialPinOutDiagram" src="https://github.com/user-attachments/assets/afe2e7ea-2d6e-40f6-9cac-fa309bbfd309" />

Untuk lebih jelasnya, berikut pin I/O digtial dan analog

<img width="2607" height="1419" alt="ArduinoUno_OfficialPinOutDiagram_DigitalIOPinsMarked" src="https://github.com/user-attachments/assets/9e0fd40c-aab0-4349-9365-a3eda627fab7" />

<h2></h2>
<a href="https://komputer.ft.unsoed.ac.id/"><img src="https://github.com/user-attachments/assets/44889372-e6f9-48ee-a9a7-8d1fa9fbcf6d" /></a>
