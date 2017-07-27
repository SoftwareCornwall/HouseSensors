<?php

include 'config.php';


// json response array
$response = array("error" => FALSE);

if (isset($_POST['email']) && isset($_POST['password'])) {

// receiving the post params
    $email = $_POST['email'];
    $password = $_POST['password'];

    $userLogin = $pdo->prepare("SELECT * FROM users WHERE email = :email");
    $userLogin->bindParam(":email", $email);
    $user = $userLogin->execute();

    $dbPassword = "";

    if ($userLogin->execute()) {
        while ($row = $userLogin->fetch()) {
            $dbPassword = $row["encrypted_password"];
            // user authentication details are correct

            if ($dbPassword == $password) {
                $response["error"] = FALSE;
                $response["uid"] = $row["unique_id"];
                $response["user"]["name"] = $row["name"];
                $response["user"]["email"] = $row["email"];
                $response["user"]["created_at"] = $row["created_at"];
                $response["user"]["updated_at"] = $row["updated_at"];
                $response["user"]["house"] = $row["house"];
                echo json_encode($response);
            } else {
// user is not found with the credentials
                $response["error"] = TRUE;
                $response["error_msg"] = "Login credentials are wrong. Please try again!";
                echo json_encode($response);
                {
// required post params is missing
                    $response["error"] = TRUE;
                    $response["error_msg"] = "Required parameters email or password is missing!";
                    echo json_encode($response);
                }

            }

        }
    }
}
