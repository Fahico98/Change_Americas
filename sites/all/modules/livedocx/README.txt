
INSTALLATION:

This module requires the PHP-SOAP package. 
  (cPanel just build easyapache with exhaustive options SOAP enabled)

Dependencies:
  - views (3.x)
  - field
  - field_ui
  - variable
  - Token (for views)
-----------------

USAGE:

1.  Create an account on www.livedocx.com
2.  Administer LiveDocx settings (admin/config/services/livedocx/settings).  
    Add your livedocx.com username and password from step 1.  Create the 
    templates directory on your server and configure the path setting.
3.  Create a MS-WORD template (Word Document (.docx)) DO NOT USE (Strict 
    Open XML Document (.docx)
   -hint- MS Office:  INSERT -> Quick Parts -> Field -> MailMerge [category]
    -> MergeField
4.  Create a new content type and add the fields that are going to be used 
    to merge with the docx template.
5.  Upload the (.docx) template file (admin/config/services/livedocx) 
    -- Click Save Template Document
6.  Configure the template settings (admin/config/services/livedocx/templates).
    Select "Node" and select the "content type" associated with this template.
    Click Save
7.  Select Add/Modify Variables
    Add each mailmerge variable from the docx template file to the 
    "New Variable" field and click Add.
    99% of the time, use Mapping: "Fields in Entity" unless you want to map the
    entity title to a docx template field variable.
    i.e.  field <<first-name>> in docx template would be "first-name" without 
    the quotes.
8.  After you have added all of the template field variables, go to your content
    type associated with this template and select the "Manage Display" tab.   
    You should see two new view modes called "LiveDocx Word" and "LiveDocx PDF".
    Configure and map each template variable you just added in step 7, to the 
    associated content type field and click save.  Make sure to do the same both
    "LiveDocx Word" and "LiveDocx PDF" view modes.
9.  Create a view that displays the content LiveDocx WORD DOCUMENT content type.
		 View Settings:
		 - Format:  Table
		 - Fields (suggested)
		    - Author
		    - Title
		    - Updated date
		    - Nid
		    - Global: Custom text
		      - Text: <img src="/sites/default/files/icons/icon_word_16.png> 
		        (google search for your favorite word doc icon.)
		      - REWRITE RESULTS:
		        - Output this field as a link [checked]
		        - Link path: node/[nid]/word						
		          (#nid token taken from the Nid field above.  
		           Nid field MUST be above/before the Global: Custom Text
		           so that value is loaded)
		        - Title text: Download Word Document
9.  Create a view that displays the content LiveDocx content types.
		 View Settings:
		 - Format:  Table
		 - Fields (suggested)
		    - Author
		    - Title
		    - Updated date
		    - Nid
		    - Global: Custom text
		      - Text: <img src="/sites/default/files/icons/icon_pdf_16.png>  
		        (google search for your favorite pdf doc icon.)
		      - REWRITE RESULTS:
		        - Output this field as a link [checked]
		        - Link path: node/[nid]/pdf						
		          (#nid token taken from the Nid field above.  
		           Nid field MUST be above/before the Global: Custom Text 
		           so that value is loaded)
		        - Title text: Download PDF Document
