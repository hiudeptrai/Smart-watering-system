<?php
session_start();
if(!isset( $_SESSION['login'])||empty($_SESSION['login'])){
    header('Location: login.php');
        die();
}
 if(isset( $_POST['logout'])){
     if (isset($_SESSION['login'])){
    unset($_SESSION['login']);
     header('Location: login.php');
     die();
}
 
 }

  
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
 
   ?>     
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Hệ thống điều khiển</title>
    <!-- <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script> -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">

	<!-- jQuery library -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>

	<!-- Popper JS -->
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>

	<!-- Latest compiled JavaScript -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"></script>
 
  
</head>
<body  align="center" style="background-image: url(https://thanglongvn.com/Systems/2015/07/13/tuoi-tieu-va-nong-nghiep.jpg)"><br />
<?php
   $jsonString = file_get_contents("test/test.json");
	$data = json_decode($jsonString, true);
 
    $v08=$data['08']; 
    $v09=$data['09']; 
    $v0A=$data['0A']; 
    $v0B=$data['0B']; 
    $v0C=$data['0C']; 
    $v0D=$data['0D']; 
    $v0E=$data['0E'];  
    $v0F=$data['0F'];  
    $v10=$data['10'];  
    $v11=$data['11'];  
    $v12=$data['12'];  
    $v13=$data['13'];  
    $v14=$data['14'];  
    $v15=$data['15'];  
    $v16=$data['16'];  
    $v17=$data['17'];  
    $v18=$data['18']; 
    $v19=$data['19']; 
    $v1A=$data['1A']; 
    $v1B=$data['1B']; 
    $v1C=$data['1C']; 
    $v1D=$data['1D']; 
    $v1E=$data['1E'];  
    $v1F=$data['1F']; 
    $v20=$data['20'];  
    $v21=$data['21'];  
    $v22=$data['22'];  
    $v23=$data['23'];
    $v3B=$data['3B']; 
    $v3C=$data['3C']; 
    $v3D=$data['3D']; 
    $v3E=$data['3E'];  
    $v3F=$data['3F'];
 ?>
 <div class="container">
	<header> 
         <h2> <span style="color:red;font-weight:500">HỆ THỐNG TƯỚI CÂY THÔNG MINH </span><br /></h2>
    </header>
    </div>
	<?php
	$servername = "localhost";
	$dbname = "id18128746_doan";
	$username = "id18128746_quanghieu";
	$password = "Matkhaumanhvl-0";
	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 

	$sql = "SELECT value1 FROM HumidityData ORDER BY reading_time DESC LIMIT 1";
	$result = $conn->query($sql);
	$row = $result->fetch_assoc();
	$hum=$row["value1"];
	$result->free();
	$conn->close();
   
	?>
	<!--<span>Độ ẩm</span><?=$hum?>-->
	<div class="container">
	<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode">Chọn chế độ tưới</button>
	<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode1">Cài đặt chế độ tưới thứ nhất</button>
	<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode2">Cài đặt chế độ tưới thứ hai</button>
	<form action="esp-control.php" method="post" style="display: inline-block;">
	<input type="submit" class="btn btn-danger" name="logout" value="Đăng xuất">
	</form>
</div>
	<div class="modal" id="setupmode">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Chọn mode tưới</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
					<form action="esp-control.php" method="post">   
						<label for="mode">Chọn mode tưới:</label>    
						<select name="08">
							<?php
								if($v08=='0'){
									echo'<option selected value="0">Không tưới</option>';
								}else{
									echo'<option value="0">Không tưới</option>';
								}
								if($v08=='1'){
									echo'<option selected value="1">Mode theo lịch</option>';
								}else{
									echo'<option value="1">Mode theo lịch</option>';
								}
								if($v08=='2'){
									echo'<option selected value="2">Mode tưới khi đất khô</option>';
								}else{
									echo'<option value="2">Mode tưới khi đất khô</option>';
								}
							?>
						</select>
						<input type="submit" class="btn btn-success" value="Lưu">
					</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>

	<!-- Start modal -->
	<div class="modal" id="setupmode1">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt Mode tưới theo lịch</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
								<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode1t1">Cài đặt cho lần tưới thứ nhất</button><br><br>
				<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode1t2">Cài đặt cho lần tưới thứ hai</button><br><br>
				<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode1t3">Cài đặt cho lần tưới thứ ba</button><br><br>
				<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#setupmode1t4">Cài đặt cho lần tưới thứ tư</button><br><br>
				<form action="esp-control.php" method="post">
					<label for="mode">Chọn mức độ ẩm cao:</label>
					<select name="09">
						<?php
							for($i=0;$i<100;$i++){
								if($i==$v09){
									echo'<option selected value="'.$i.'">'.$i.'</option>';
								}else{
									echo'<option value="'.$i.'">'.$i.'</option>';
								}
							}
						?>
					</select><br>
					<input type="submit" class="btn btn-success" value="Lưu">
						
				</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>
	<!-- End modal -->

		<!-- Start modal -->
	<div class="modal" id="setupmode1t1">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt lần tưới thứ nhất Mode tưới theo lịch</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
				<form action="esp-control.php" method="post">
					<label for="mode">Bật/Tắt lần tưới:</label>
					<select name="0C">
						<?php
							if($v0C=='1'){
								echo'<option value="0">Tắt</option>
								<option selected value="1">Bật</option>';
							}else{
								echo'<option selected  value="0">Tắt</option>
								<option value="1">Bật</option>';
							}
						?>
					</select><br>
					<label for="mode">Chọn giờ bắt đầu tưới:</label>
						<select name="0A">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v0A){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút bắt đầu tưới:</label>   
						<select name="0B">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v0B){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn thời lượng mỗi lần tưới:</label>   
						<select name="0D">
							<?php
								for($i=1;$i<60;$i++){
									if($i==$v0D){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn tần suât tưới:</label>   
						<select name="0E">
							<?php
								for($i=1;$i<11;$i++){
									if($i==$v0E){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
					<input type="submit" class="btn btn-success" value="Lưu">
						
				</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>
	<!-- End modal -->

	<!-- Start modal -->
	<div class="modal" id="setupmode1t2">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt lần tưới thứ hai Mode tưới theo lịch</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
				<form action="esp-control.php" method="post">
					<label for="mode">Bật/Tắt lần tưới:</label>
					<select name="11">
						<?php
							if($v11=='1'){
								echo'<option value="0">Tắt</option>
								<option selected value="1">Bật</option>';
							}else{
								echo'<option selected  value="0">Tắt</option>
								<option value="1">Bật</option>';
							}
						?>
					</select><br>
					<label for="mode">Chọn giờ bắt đầu tưới:</label>
						<select name="0F">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v0F){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút bắt đầu tưới:</label>   
						<select name="10">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v10){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn thời lượng mỗi lần tưới:</label>   
						<select name="12">
							<?php
								for($i=1;$i<60;$i++){
									if($i==$v12){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn tần suât tưới:</label>   
						<select name="13">
							<?php
								for($i=1;$i<11;$i++){
									if($i==$v13){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
					<input type="submit" class="btn btn-success" value="Lưu">
						
				</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>
	<!-- End modal -->

	<!-- Start modal -->
	<div class="modal" id="setupmode1t3">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt lần tưới thứ ba Mode tưới theo lịch</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
				<form action="esp-control.php" method="post">
					<label for="mode">Bật/Tắt lần tưới:</label>
					<select name="16">
						<?php
							if($v16=='1'){
								echo'<option value="0">Tắt</option>
								<option selected value="1">Bật</option>';
							}else{
								echo'<option selected  value="0">Tắt</option>
								<option value="1">Bật</option>';
							}
						?>
					</select><br>
					<label for="mode">Chọn giờ bắt đầu tưới:</label>
						<select name="14">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v14){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút bắt đầu tưới:</label>   
						<select name="15">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v15){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn thời lượng mỗi lần tưới:</label>   
						<select name="17">
							<?php
								for($i=1;$i<60;$i++){
									if($i==$v17){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn tần suât tưới:</label>   
						<select name="18">
							<?php
								for($i=1;$i<11;$i++){
									if($i==$v18){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
					<input type="submit" class="btn btn-success" value="Lưu">
						
				</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>
	<!-- End modal -->

	<!-- Start modal -->
	<div class="modal" id="setupmode1t4">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt lần tưới thứ tư Mode tưới theo lịch</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
				<form action="esp-control.php" method="post">
					<label for="mode">Bật/Tắt lần tưới:</label>
					<select name="1B">
						<?php
							if($v1B=='1'){
								echo'<option value="0">Tắt</option>
								<option selected value="1">Bật</option>';
							}else{
								echo'<option selected  value="0">Tắt</option>
								<option value="1">Bật</option>';
							}
						?>
					</select><br>
					<label for="mode">Chọn giờ bắt đầu tưới:</label>
						<select name="19">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v19){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút bắt đầu tưới:</label>   
						<select name="1A">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v1A){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn thời lượng mỗi lần tưới:</label>   
						<select name="1C">
							<?php
								for($i=1;$i<60;$i++){
									if($i==$v1C){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn tần suât tưới:</label>   
						<select name="1D">
							<?php
								for($i=1;$i<11;$i++){
									if($i==$v1D){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
					<input type="submit" class="btn btn-success" value="Lưu">
						
				</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div>
	<!-- End modal -->
	
	<!-- Start modal -->
		<div class="modal" id="setupmode2">
		<div class="modal-dialog">
			<div class="modal-content">
			
				<!-- Modal Header -->
				<div class="modal-header">
					<h4 class="modal-title">Cài đặt chế độ tưới thứ hai</h4>
					<button type="button" class="close" data-dismiss="modal">&times;</button>
				</div>
					<!-- Modal body -->
				<div class="modal-body">
				<form action="esp-control.php" method="post">   
						<label for="mode">Chọn giờ bắt đầu không tưới:</label>
						<select name="1E">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v1E){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút bắt đầu không tưới:</label>   
						<select name="1F">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v1F){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn giờ kết thúc không tưới:</label>  
						<select name="20">
							<?php
								for($i=0;$i<24;$i++){
									if($i==$v20){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn phút kết thúc không tưới:</label>   
						<select name="21">
							<?php
								for($i=0;$i<60;$i++){
									if($i==$v21){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn mức độ ẩm tối thiểu:</label>  
						<select name="22">
							<?php
								for($i=0;$i<100;$i++){
									if($i==$v22){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<label for="mode">Chọn thời lượng mỗi lần tưới:</label>   
						<select name="23">
							<?php
								for($i=1;$i<60;$i++){
									if($i==$v23){
										echo'<option selected value="'.$i.'">'.$i.'</option>';
									}else{
										echo'<option value="'.$i.'">'.$i.'</option>';
									}
								}
							?>
						</select><br>
						<input type="submit" class="btn btn-success" value="Lưu">
						
					</form>
				</div>
					
					<!-- Modal footer -->
				<div class="modal-footer">
					<button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
				</div>
				
			</div>
		</div>
	</div><br>
	<!-- End modal -->
	<div class="container">
	<?php
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

		$sql='select count(id) as number from HumidityData';
		$result =mysqli_query($conn, $sql);
        $data =[];
        while($row=mysqli_fetch_array($result,1)){
        $data[]=$row;
        }
        $result = $data;
		$number=0;
		if($result!=null&&count($result)>0){
			$number=$result[0]['number'];
		}
		define('max_slot', '10');
		$pages = ceil($number/max_slot);
		$current_page=1;
		if(isset($_GET['page'])){
			$current_page=$_GET['page'];
		}
		$index=($current_page-1)*max_slot;
		$sql = 'select * from HumidityData ORDER BY id DESC limit '.$index.','.max_slot.'';
		//$memberlist = executeResult($sql);


//$sql = "SELECT id, sensor, location, value1, reading_time FROM HumidityData ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5" class="table table-bordered" style="background-color:white">
      <tr> 
         <td class="font-weight-bold">Timestamp</td> 
        <td class="font-weight-bold">Sensor</td> 
        <td class="font-weight-bold">Location</td> 
        <td class="font-weight-bold">Value</td> 
        
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_sensor = $row["sensor"];
        $row_location = $row["location"];
        $row_value1 = $row["value1"];
        $row_reading_time = $row["reading_time"];
      if($row_value1<$v22){
        echo '<tr>
                 <td style="color:red">'. $row_reading_time .'</td>
                <td style="color:red">' . $row_sensor . '</td> 
                <td style="color:red">' . $row_location . '</td> 
                <td style="color:red">' . $row_value1 . ' %</td> 
                 
              </tr>';
      }else if($row_value1>$v09){
          echo '<tr> 
                 <td style="color:blue">' . $row_reading_time . '</td> 
                <td style="color:blue">' . $row_sensor . '</td> 
                <td style="color:blue">' . $row_location . '</td> 
                <td style="color:blue">' . $row_value1 . ' %</td> 
                
              </tr>';
      }
      else{
          echo '<tr> 
                 <td>' . $row_reading_time . '</td>
                <td>' . $row_sensor . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_value1 . ' %</td> 
                 
              </tr>';
      }
    }
    $result->free();
}

$conn->close();
?>

<div class="row">
			<ul class="pagination" style="margin-left:15px">
				<?php
				if($current_page>1){echo '<li class="page-item"><a class="page-link" href="esp-control.php?page='.($current_page-1).'"><</a></li>';}	
				if($pages<6)	{ 		
				for($i=1;$i<=$pages;$i++){
					if($i==$current_page){ 
						echo '<li class="page-item active"><a class="page-link" href="esp-control.php?page='.$i.'" >'.$i.'</a></li>';
					}else{
						echo '<li class="page-item"><a class="page-link" href="esp-control.php?page='.$i.'">'.$i.'</a></li>';
					}
					}
				}else{
					if(($current_page-2)>1) {echo '<li class="page-item"><a class="page-link" href="#">...</a></li>';}
					if($current_page<3){$begin=1;$end=5;}
					else if($current_page>$pages-2){$begin=$pages-4;$end=$pages;}
					else {$begin=$current_page-2;$end=$current_page+2;}
					for($i=$begin;$i<=$end;$i++){
						if($i==$current_page){ 
							echo '<li class="page-item active"><a class="page-link" href="esp-control.php?page='.$i.'" >'.$i.'</a></li>';
						}else{
							echo '<li class="page-item"><a class="page-link" href="esp-control.php?page='.$i.'">'.$i.'</a></li>';
						}
					}
					if(($current_page+2)<$pages) {echo '<li class="page-item"><a class="page-link" href="#">...</a></li>';}
				}

				if($current_page<$pages){echo '<li class="page-item"><a class="page-link" href="esp-control.php?page='.($current_page+1).'">></a></li>';}
				?>
			</ul>
		</div>

 </div>
 
</body>
</html>