<?php

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "id18128746_doan";
// REPLACE with Database user
$username = "id18128746_quanghieu";
// REPLACE with Database user password
$password = "Matkhaumanhvl-0";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $sensor = $location = $value1 = $uart_name = $uart_value= "";


if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if(isset($_POST["api_key"])){
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $sensor = test_input($_POST["sensor"]);
        $location = test_input($_POST["location"]);
        $value1 = test_input($_POST["value1"]);
        date_default_timezone_set('Asia/Ho_Chi_Minh');
        $cr_date = date('Y-m-d H:i:s');
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        // $sql="select (DAY(reading_time)) AS oldday from HumidityData ORDER BY reading_time DESC  LIMIT 1";
        // $result =mysqli_query($conn, $sql);
        // $row=mysqli_fetch_array($result,1);
        // $oldday=$row['oldday'];
        // $today=date("d");
        
        // if($today!=$oldday){
        //     $sql="DELETE from HumidityData";
        //     $conn->query($sql);
        //     $oldday=$today;
        // }
        
        $sql = "INSERT INTO HumidityData (sensor, location, value1, reading_time)
        VALUES ('" . $sensor . "', '" . $location . "', '" . $value1 . "', '" . $cr_date . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}else {
    $jsonString = file_get_contents("test/test.json");
   $data = json_decode($jsonString, true);
   
   if(isset($_POST['08']))  {  $data['08'] = $_POST['08'];	}
	if(isset($_POST['09']))  {  $data['09'] = $_POST['09'];	}
	if(isset($_POST['0A']))  {  $data['0A'] = $_POST['0A'];	}
	if(isset($_POST['0B']))  {  $data['0B'] = $_POST['0B'];	}
	if(isset($_POST['0C']))  {  $data['0C'] = $_POST['0C'];	}
	if(isset($_POST['0D']))  {  $data['0D'] = $_POST['0D'];	}
	if(isset($_POST['0E']))  {  $data['0E'] = $_POST['0E'];	}
	if(isset($_POST['0F']))  {  $data['0F'] = $_POST['0F'];	}
	if(isset($_POST['10']))  {  $data['10'] = $_POST['10'];	}
	if(isset($_POST['11']))  {  $data['11'] = $_POST['11'];	}
	if(isset($_POST['12']))  {  $data['12'] = $_POST['12'];	}
	if(isset($_POST['13']))  {  $data['13'] = $_POST['13'];	}
	if(isset($_POST['14']))  {  $data['14'] = $_POST['14'];	}
	if(isset($_POST['15']))  {  $data['15'] = $_POST['15'];	}
	if(isset($_POST['16']))  {  $data['16'] = $_POST['16'];	}
	if(isset($_POST['17']))  {  $data['17'] = $_POST['17'];	}
	if(isset($_POST['18']))  {  $data['18'] = $_POST['18'];	}
	if(isset($_POST['19']))  {  $data['19'] = $_POST['19'];	}
	if(isset($_POST['1A']))  {  $data['1A'] = $_POST['1A'];	}
	if(isset($_POST['1B']))  {  $data['1B'] = $_POST['1B'];	}
	if(isset($_POST['1C']))  {  $data['1C'] = $_POST['1C'];	}
	if(isset($_POST['1D']))  {  $data['1D'] = $_POST['1D'];	}
	if(isset($_POST['1E']))  {  $data['1E'] = $_POST['1E'];	}
	if(isset($_POST['1F']))  {  $data['1F'] = $_POST['1F'];	}
	if(isset($_POST['20']))  {  $data['20'] = $_POST['20'];	}
	if(isset($_POST['21']))  {  $data['21'] = $_POST['21'];	}
	if(isset($_POST['22']))  {  $data['22'] = $_POST['22'];	}
	if(isset($_POST['23']))  {  $data['23'] = $_POST['23'];	}
	if(isset($_POST['3B']))  {  $data['3B'] = $_POST['3B'];	}
	if(isset($_POST['3C']))  {  $data['3C'] = $_POST['3C'];	}
	if(isset($_POST['3D']))  {  $data['3D'] = $_POST['3D'];	}
	if(isset($_POST['3E']))  {  $data['3E'] = $_POST['3E'];	}
	if(isset($_POST['3F']))  {  $data['3F'] = $_POST['3F'];	}
   
   $newJsonString = json_encode($data);
	file_put_contents("test/test.json", $newJsonString);
}
}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}