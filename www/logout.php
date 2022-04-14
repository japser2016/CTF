<?php
	session_start();
	if ($_SESSION['login'] == null) {
		header("Location: admin.php");
		exit;
	}
    else {
        session_destroy();
        echo '<!DOCTYPE html>
<html>
<head>
<title>Logout</title>
<link rel="stylesheet" type="text/css" href="yui.2.css" />
<link rel="stylesheet" type="text/css" href="global.6.css" />
</head>
<body>
<h2>You are now logged out.</h2>
<p><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>FLAG: key{85cb1f7433482da0861d309a58df5b6cb642b6211683bfbcd0a38b6fc99b303d}</p>
</body>
</html>';}
?>
