<?php

class Posts
{

    protected $pdo;

    public function __construct($pdo) {
        $this->pdo = $pdo;
    }

    public function createPost($title, $content, $authorId) {
        $targetDir = "uploads/";
        $imageFileType = strtolower(pathinfo($_FILES["image"]["name"], PATHINFO_EXTENSION));
        $targetFile = $targetDir . time() . "_" . uniqid() . "." . $imageFileType;
    

        if (!empty($_FILES["image"]["tmp_name"])) {

            if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "gif") {
                return "Omlouváme se, pouze JPG, JPEG, PNG & GIF soubory jsou povoleny.";
            }
    
            // Kontrola velikosti souboru
            if ($_FILES["image"]["size"] > 500000) {
                return "Omlouváme se, váš soubor je příliš velký.";
            }
    
            // Pokus o nahrání souboru
            if (!move_uploaded_file($_FILES["image"]["tmp_name"], $targetFile)) {
                return "Omlouváme se, došlo k chybě při nahrávání souboru.";
            }
        }
        
        try {
            $stmt = $this->pdo->prepare("INSERT INTO posts (title, description, image, author, date) VALUES (:title, :content, :path, :authorId, NOW())");
            $stmt->bindParam(':title', $title);
            $stmt->bindParam(':content', $content);
            $stmt->bindParam(':authorId', $authorId);
            $stmt->bindParam(':path', $targetFile);

            if ($stmt->execute()) {
                echo "Příspěvek přidán";
            } else {
                echo "Příspěvek nebylo možné přidat";
            }
        } catch (PDOException $e) {
            return "Chyba databáze: " . $e->getMessage();
        }
    }

    public function getPosts($id=null)
    {
        if ($id==null) {
            $sql = "SELECT p.*, u.username, u.profile_pic, u.position FROM posts p
            JOIN users u ON p.author = u.id
            ORDER BY p.id DESC";
            $stmt = $this->pdo->prepare($sql);
        }
        else {
            $sql = "SELECT p.*, u.username, u.profile_pic, u.position FROM posts p
            JOIN users u ON p.author = u.id WHERE p.id=:id";
            $stmt = $this->pdo->prepare($sql);
            $stmt->bindParam(":id", $id, \PDO::PARAM_INT);
        }


        $stmt->execute();
    
        $results = $stmt->fetchAll(\PDO::FETCH_ASSOC);
    
        $posts = [];
    
        foreach ($results as $result) {
            $description = explode(".", $result["description"]);
            $description = $description[0];
            $dom = new DOMDocument();
            $dom->loadHTML(mb_convert_encoding($description, 'HTML-ENTITIES', 'UTF-8'), LIBXML_HTML_NOIMPLIED | LIBXML_HTML_NODEFDTD);

            // Získání všech elementů obsahu
            $elements = $dom->getElementsByTagName('*');

            // Zavření všech otevřených tagů
            foreach ($elements as $element) {
                $tag = $element->tagName;
                $openTag = "<{$tag}>";
                $closeTag = "</{$tag}>";
                
                $html = $element->ownerDocument->saveHTML($element);
                if (substr_count($html, $openTag) > substr_count($html, $closeTag)) {
                    $element->parentNode->removeChild($element);
                }
            }

            // Získání upraveného textu
            $cleanedDescription = $dom->saveHTML();

            // Odstranění zbytečných záhlaví HTML
            $cleanedDescription = preg_replace('/^<!DOCTYPE.+?>/', '', $cleanedDescription);
            $cleanedDescription = preg_replace('/^<html>.+<body>/', '', $cleanedDescription);
            $cleanedDescription = preg_replace('/<\/body>.+<\/html>$/', '', $cleanedDescription);

            $timestamp = strtotime($result['date']);
            $date = date("j.n. Y", $timestamp);

            $post = new \stdClass();
            $post->id = $result['id'];
            $post->title = $result['title'];
            $post->description = $result['description'];
            $post->shortDescription = $cleanedDescription;
            $post->image = $result['image'];
            $post->date = $date;

    
            // Informace o autorovi
            $post->author = new \stdClass();
            $post->author->username = $result['username'];
            $post->author->profile_pic = $result['profile_pic'];
            $post->author->position = $result['position'];
    
            $posts[] = $post;
        }
    
        return $posts;
    }

    public function updatePost($postId, $title, $content, $authorId) {
        $targetDir = "uploads/";
        $imageFileType = strtolower(pathinfo($_FILES["image"]["name"], PATHINFO_EXTENSION));
        $targetFile = $targetDir . time() . "_" . uniqid() . "." . $imageFileType;
    
        if (!empty($_FILES["image"]["tmp_name"]) OR $_FILES["image"]["size"] <= 5) {
            if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "gif") {
                return "Omlouváme se, pouze JPG, JPEG, PNG & GIF soubory jsou povoleny.";
            }
    
            // Kontrola velikosti souboru
            if ($_FILES["image"]["size"] > 500000 OR $_FILES["image"]["size"] < 5) {
                return "Omlouváme se, váš soubor je příliš velký.";
            }
    
            // Pokus o nahrání souboru
            if (!move_uploaded_file($_FILES["image"]["tmp_name"], $targetFile)) {
                return "Omlouváme se, došlo k chybě při nahrávání souboru.";
            }
        } else {
            // Pokud nebyla nahrána nová obrázek, použijte stávající cestu k obrázku
            $existingPost = $this->getPosts($postId);
            $targetFile = $existingPost->image;
        }
    
        try {
            $stmt = $this->pdo->prepare("UPDATE posts SET title = :title, description = :content, image = :path, author = :authorId, date = NOW() WHERE id = :postId");
            $stmt->bindParam(':title', $title);
            $stmt->bindParam(':content', $content);
            $stmt->bindParam(':authorId', $authorId);
            $stmt->bindParam(':path', $targetFile);
            $stmt->bindParam(':postId', $postId);
    
            if ($stmt->execute()) {
                echo "Příspěvek aktualizován";
            } else {
                echo "Příspěvek nebylo možné aktualizovat";
            }
        } catch (PDOException $e) {
            return "Chyba databáze: " . $e->getMessage();
        }
    }

    public function getPost($id) 
    {

        $sql = "SELECT * FROM posts WHERE id=:id";
        $stmt = $this->pdo->prepare($sql);
        $stmt->bindParam(":id", $id, \PDO::PARAM_INT);

        $stmt->execute();

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        return $result;

    }

    public function deletePost($id)
    {
        $sql = "DELETE FROM posts WHERE id=:id";
        $stmt = $this->pdo->prepare($sql);
        $stmt->bindParam(":id", $id, \PDO::PARAM_INT);

        $stmt->execute();
    }

}