#ifndef WEBCONTENT_H
#define WEBCONTENT_H

const char custom_html[] PROGMEM = R"rawliteral(
    <label for='location'>Оберіть свій регіон:</label><br>
    <select id='region_id' name='region_select' onchange="updateTextBox()">
        <option value='' disabled selected>--Регіон--</option>
        <option value='3'>Хмельницька область</option>
        <option value='4'>Вінницька область</option>
        <option value='5'>Рівненська область</option>
        <option value='8'>Волинська область</option>
        <option value='9'>Дніпропетровська область</option>
        <option value='10'>Житомирська область</option>
        <option value='11'>Закарпатська область</option>
        <option value='12'>Запорізька область</option>
        <option value='13'>Івано-Франківська область</option>
        <option value='14'>Київська область</option>
        <option value='15'>Кіровоградська область</option>
        <option value='16'>Луганська область</option>
        <option value='17'>Миколаївська область</option>
        <option value='18'>Одеська область</option>
        <option value='19'>Полтавська область</option>
        <option value='20'>Сумська область</option>
        <option value='21'>Тернопільська область</option>
        <option value='22'>Харківська область</option>
        <option value='23'>Херсонська область</option>
        <option value='24'>Черкаська область</option>
        <option value='25'>Чернігівська область</option>
        <option value='26'>Чернівецька область</option>
        <option value='27'>Львівська область</option>
        <option value='28'>Донецька область</option>
        <option value='29'>Автономна Республіка Крим</option>
        <option value='30'>м. Севастополь</option>
        <option value='31'>м. Київ</option>
    </select>
    <br>
<script>
    document.addEventListener('DOMContentLoaded', function() {
        document.getElementById('alert_location').setAttribute('readonly', 'true');
    });

    function updateTextBox() {
        var select = document.getElementById('region_id');
        document.getElementById('alert_location').value = select.options[select.selectedIndex].value;
    }
</script>
)rawliteral";

#endif
