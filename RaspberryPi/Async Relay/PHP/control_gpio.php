<?php
// Function to set GPIO pin mode
function setPinMode($pin, $mode) {
    $command = "gpio mode $pin $mode";
    exec($command);
}

// Function to write to GPIO pin
function writePin($pin, $value) {
    $command = "gpio write $pin $value";
    exec($command);
}

// Function to read from DHT11 sensor
function readDHT11() {
    $command = "Adafruit_DHT 11 4";
    exec($command, $output);
    $data = explode(",", $output[0]);
    $humidity = $data[0];
    $temperature = $data[1];
    return array($humidity, $temperature);
}

// Control GPIO pins based on form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["led1"])) {
        $led1_state = intval($_POST["led1"]);
        setPinMode(21, "out");
        writePin(21, $led1_state);
    }
    if (isset($_POST["led2"])) {
        $led2_state = intval($_POST["led2"]);
        setPinMode(22, "out");
        writePin(22, $led2_state);
    }
    if (isset($_POST["led3"])) {
        $led3_state = intval($_POST["led3"]);
        setPinMode(23, "out");
        writePin(23, $led3_state);
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Raspberry Pi Control</title>
</head>
<body>
    <h1>Raspberry Pi Control</h1>

    <h2>DHT11 Sensor</h2>
    <?php
    list($humidity, $temperature) = readDHT11();
    if ($humidity !== false && $temperature !== false) {
        echo "<p>Temperature: $temperature°C</p>";
        echo "<p>Humidity: $humidity%</p>";
    } else {
        echo "<p>Error: Failed to read sensor data.</p>";
    }
    ?>

    <h2>LED Control</h2>
    <form method="post">
        <label for="led1">LED 1:</label>
        <input type="checkbox" name="led1" value="1">
        <br>
        <label for="led2">LED 2:</label>
        <input type="checkbox" name="led2" value="1">
        <br>
        <label for="led3">LED 3:</label>
        <input type="checkbox" name="led3" value="1">
        <br>
        <input type="submit" value="Apply Changes">
    </form>
</body>
</html>
