<?php
session_start();
if(isset($_SESSION['login'])){
    if($_SESSION['login']=="true"){
        header('Location: esp-control.php');
        die();
    }
}
if(isset($_POST['pwd'])){
    $passin=$_POST['pwd'];
    $jsonString = file_get_contents("test/test.json");
	$data = json_decode($jsonString, true);
    $pass1=$data['3C']; 
    $pass2=$data['3D']; 
    $pass3=$data['3E'];  
    $pass4=$data['3F'];
    
    if($pass1==$passin[0]&&$pass2==$passin[1]&&$pass3==$passin[2]&&$pass4==$passin[3]){
        $_SESSION['login']="true";
        header('Location: esp-control.php');
        die();
    }
    
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <title>Document</title>
</head>
<body style="background-image: url(https://thanglongvn.com/Systems/2015/07/13/tuoi-tieu-va-nong-nghiep.jpg)">
    <div class="container">
    <h1 style="color:#FF0000; margin-top:200px">Hệ thống tưới cây thông minh</h1>
    <form class="form-horizontal" action="login.php" method="post">
  
  <div class="form-group">
    <label for="pwd" style="color:#FF0000">Mật khẩu: </label>
    <input type="password" class="form-control" name="pwd">
  </div>
  <div class="form-group" >
  <button type="submit" class="btn btn-success">Đăng nhập</button>
  </div>
</form>
</div>
</body>
</html>