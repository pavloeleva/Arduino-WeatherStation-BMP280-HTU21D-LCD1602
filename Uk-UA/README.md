<!-- <h1 align="center"><a href="https://github.com/pavloeleva/Arduino-WeatherStation-BMP280-HTU21D-LCD1602/blob/main/README.md">Arduino-WeatherStation-BMP280-HTU21D-LCD1602</a></h1> -->
<h1 align="center">Метеостанція Arduino</h1>
<div id="badges_img" align="center">
  <a href=""><img src="https://img.shields.io/badge/STEM-education-blue" /></a>
  <img src="https://img.shields.io/badge/arduino-project-yellowgreen" alt=""/>&nbsp;
  <img src="https://img.shields.io/badge/arduino-learning-orange"/>  
  <img src="https://img.shields.io/badge/GeekOn!-STEM--club-green"/>
</div>
<p><strong><em>Проєкт для навчання та створення діючого приладу</em></strong></p>
<h2><strong>Про проєкт</strong></h2>
<div id="geekon_logo" align="left">
  <a href="https://github.com/pavloeleva/Arduino-WeatherStation-BMP280-HTU21D-LCD1602/blob/main/Uk-UA/README.md#%D0%BF%D1%80%D0%BE-%D0%BF%D1%80%D0%BE%D1%94%D0%BA%D1%82"><img width="100" src="https://github.com/pavloeleva/Arduino-WeatherStation-BMP280-HTU21D-LCD1602/blob/main/Uk-UA/IMG/logo_geekon.png" alt=""/></a>
</div>
<p>Цей проєкт створений для занять у СТЕМ-клубі GeekOn!</p>

<p>Метою проєкту є:</p>
<ul>
  <li>побудова пристрою, що може використовуватися у побуті та при вивченні природничих наук;</li>
  <li>узагальнення технологій підключення пристроїв та програмування мікроконтролерів у середовищі Arduino.</li>
</ul>
<h3>Теми, де можна використовувати дану метеостанцію</h3>
<ul>
  <li>Температура та її вимірювання. Термометри.</li>
  <li>Атмосферний тиск
    <ul>
      <li>Одиниці вимірювання атмосферного тиску</li>
      <li>Залежність атмосферного тиску від висоти</li>
    </ul>
  </li>
  <li>Відносна вологість повітря</li>  
</ul>
<p>З наведених тем можна проводити як заняття у СТЕМ-клубі, так і використовувати пристрій на уроках згідно навчальних програм з того чи іншого предмету.</p>
<h3>Технології, що узагальнюються в ході виконання проєкту</h3>
<ul>
  <li>Підключення пристроїв по шині <strong>I2C</strong></li>
  <li>Використання сторонніх бібліотек у середовищі <strong>Arduino IDE</strong></li>
  <li>Програмна обробка брязкоту контактів (кнопки)</li>
  <li>Виведення інформації на LCD-дисплей</li>
</ul>
<p>&nbsp;</p>
<h2>Схема установки та опис її компонентів</h2>
<p>Схему установки, зібраної на безпаєчній монтажній платі, показано на малюнку. За необхідності створення пристрою на постійній основі, доцільно зпаяти всі з'єднання та подбати про корпус для пристрою.</p>
<div id="sheme" align="center">
  <img width="600" src="https://github.com/pavloeleva/Arduino-WeatherStation-BMP280-HTU21D-LCD1602/blob/main/Uk-UA/IMG/sheme.PNG" alt="Схема установки" />
  <p><em>Схема установки</em></p>
</div>
<p>Всі модулі, що задіяні у схемі, живляться від виходів $3{,}3\,V$ та $5\,V$ плати Arduino.</p>
<h3>Список компонентів, що задіяні у проєкті</h3>
<ul>
  <li>Плата розробника <strong>Arduino Uno</strong> або <strong>Arduino Nano</strong></li>
  <li>Безпаячна макетна плата</li>
  <li>Модуль тактової кнопки</li>
  <li>Модуль датчика тиску та температури <strong>BMP280</strong></li>
  <li>Модуль датчика температури та вологості <strong>HTU21D</strong></li>
  <li>Дисплей <strong>LCD1602</strong> з модулем <strong>I2C</strong></li>
  <li>З'єднувальні проводи (dupon або інші)</li>
</ul>
