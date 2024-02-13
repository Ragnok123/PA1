<?php 
include "../assets/config.php";

switch($_POST["type"]) {
    case "userLogin":
        $security->getLogin($_POST["username"], hash("sha256", $_POST["password"]));
        break;
    case "userRegister":
        $security->register($_POST["username"], hash("sha256", $_POST["password"]), $_POST["role"], $_POST["function"], $_POST["discord"]);
        break;
    case "updateUser":
        $security->updateUser($_POST["userId"], $_POST["username"], hash("sha256", $_POST["password"]), $_POST["role"], $_POST["profile_picture"]);
        break;
    case "removeUser":
        $posts->deletePost($_POST["post-id"]);
        break;
    case "addPost":
        $posts->createPost($_POST["title"], $_POST["content"], $_SESSION["user_id"]);
        break;
    case "updatePost":
        $posts->updatePost($_POST["post-id"], $_POST["title"], $_POST["content"], $_SESSION["user_id"]);
        break;
    case "deletePost":
        $posts->deletePost($_POST["post-id"]);
        break;
    case "removeCarousel":
        $carousel->removeImage($_POST["id"]);
        echo "success";
        break;
    case "removeGallery":
        $gallery->removeImage($_POST["id"]);
        echo "success";
        break;

    default:

        break;
}

?>