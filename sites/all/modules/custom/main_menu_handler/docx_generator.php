
<?php

   function generateFile($input){

      createReportTable();

      $templateFileName = 'template/Formato_Informe_Final_Inteligencia Estratégica_1.0.docx';
      $lastId = lastReportId();
      $fileId = str_pad($lastId, 8, '0', STR_PAD_LEFT);
      $fileName = "informe_" . $fileId . ".docx";
      $folder = "template";
      $filepath = $folder . '/' . $fileName;

      try{
         if (!file_exists($folder)){
            mkdir($folder);
         }
         copy($templateFileName, $filePath);
         $zip = new ZipArchive;
         if($zip->open($filePath) === TRUE){
            $keyFileName = 'word/document.xml';
            $content = $zip->getFromName($keyFileName);
            $timestamp = date('d-M-Y');

            /*
            $message = str_replace("client_full_name",      "onlinecode org",       $message);
            $message = str_replace("client_email_address",  "ingo@onlinecode.org",  $message);
            $message = str_replace("date_today",            $timestamp,             $message);
            $message = str_replace("client_website",        "<a class="vglnk" href="http://www.onlinecode.org" rel="nofollow"><span>www</span><span>.</span><span>onlinecode</span><span>.</span><span>org</span></a>", $message);
            $message = str_replace("client_mobile_number",  "+1999999999",          $message);
            */

            $zip->addFromString($keyFileName, $content);
            $zip->close();
         }
      }catch(Exception $e){
         echo($e->getMessage());
      }
   }

   function lastReportId(){
      try{
         $queryResult = db_query("SELECT id FROM c_a_drupal_report ORDER BY id DESC");
         foreach($queryResult as $row){
            $lastId = $row->id;
            break;
         }
      }catch(Exception $e){
         echo($e->getMessage());
      }
      return(intval($lastId, 10));
   }

   function createReportTable(){
      try{
         $queryResult = db_query(
            "CREATE TABLE IF NOT EXISTS c_a_drupal_report (
               id                INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
               file_name         VARCHAR(255) NOT NULL UNIQUE,
               status            VARCHAR(100),
               user_id           INT
            )"
         );
      }catch(Exception $e){
         echo($e->getMessage());
      }
   }

?>
