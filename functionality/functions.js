/**
    -----------------------------------------------------------------------------------------------------------------------------
    WebSocket functions
    -----------------------------------------------------------------------------------------------------------------------------
**/

var currentPath; 

/**
  *
  *  This function handles the connectivity between the nopoll (C-Websocket Implementation) server and the javascript client.   
  *  It also checks, if the websocket functionality is supported by the acting browser.
  *  It returns the socket object.
  *
  **/

function connectToZSSocket ()
{
    // Check if websockets are supported
    if ("WebSocket" in window) {
        var socket = new WebSocket("ws://localhost:1234/*");
        socket.readystate = socket.CONNECTING;
        
        return socket; 
    } else {
        window.alert("ERROR: Sorry, your browser doesn´t support websockets. You may not use functions, like delete or upload.");
    }
}

/**
  *
  *  This function reads the file, which is uploaded to the input tag.
  *  It also calls the sendFile function, which sends the uploaded file to the nopoll Server.
  *
  **/

function readUploadedFile ()
{
    var file = document.getElementById("file_input");
    var fileToSend;

    if (file.files[0].length < 1){
        alert("Please select a file!");
        return;
    }
    
    var reader = new FileReader();
    reader.onload = function (evt) {
            fileToSend = reader.result;
            sendFile(fileToSend, file.files[0].name);
        }   
    reader.readAsArrayBuffer(file.files[0]);
}

/**
  *
  *  This function is called, by clicking the delete button.
  *  It packs a msg header (ZSFDEL) with the filePath of the chosen file.
  *
  **/

function deleteFile (filePath)
{
    socket = connectToZSSocket();

    socket.onopen = function() {
        socket.readystate = socket.OPEN;  
        
        var puf = new ArrayBuffer(filePath.length+6); 
        var dataView = new DataView(puf);   //A bytesized dataview of the given arraybuffer

        // These functions set a ZSFDEL header, for ZeroSync File DELETE
        // The server needs to know, that the following path is a file, which is chosen to delete
        dataView.setUint8(0, 'Z'.charCodeAt(0));        
        dataView.setUint8(1, 'S'.charCodeAt(0));
        dataView.setUint8(2, 'F'.charCodeAt(0));
        dataView.setUint8(3, 'D'.charCodeAt(0));        
        dataView.setUint8(4, 'E'.charCodeAt(0));
        dataView.setUint8(5, 'L'.charCodeAt(0));

        // This loop sets the filePath with it´s char codes
        for (var y=0; y<filePath.length; y++) {
            dataView.setUint8(y+6, filePath.charCodeAt(y));
        }
        socket.send(puf); //send DEL command and the filePath

        console.log("Connection closing...");
        socket.readystate = socket.CLOSING;
        socket.close();
    }
       
    // Error handler 
    socket.onerror = function(e) {
        alert("Error! " + e.data);
        return;
    }

    // Handler for the server answers
    socket.onmessage = function(e) {
        console.log("Server says: "+e.data);
    }

    // Close handler
    socket.onclose = function(e) {
        console.log("Connection closed. Getting ready for new connections!");
        socket.readystate = socket.CLOSED;
        location.reload();
    }
} 

/**
  *
  *  This function contains the sending functionality for the files.
  *  A file gets sliced in 1024 Byte parts. Every part is a standalone frame and will be send to the server.
  *  Every whole filetransfer process has one initilizing message first, with a ZSF (ZeroSync File) header,
  *  4 Byte representing the whole file size and the name of the file.   
  *
  **/

function sendFile (file, name)
{
    socket = connectToZSSocket();
    fullName = currentPath+"/"+name;
    alert(fullName);    

    socket.onopen = function() {
        socket.readystate = socket.OPEN;
        var puf = new ArrayBuffer(7+fullName.length);
        var dataView = new DataView(puf);

        // This functions send an initializing command 'ZSF' for ZeroSync File
        // It´s for the server to know, that a file is incoming
        dataView.setUint8(0, 'Z'.charCodeAt(0));
        dataView.setUint8(1, 'S'.charCodeAt(0));
        dataView.setUint8(2, 'F'.charCodeAt(0));

        dataView.setUint32(3, file.byteLength);     //the 4-Bytes to represent the filesize
        
        for (var y=0; y<fullName.length; y++) {
            dataView.setUint8(y+7, fullName.charCodeAt(y));
        }
        
        socket.send(puf); //send command with length of the file´s bytes
        
        //start algorithmn: Algorithmn to slice 1024 bytes fileparts and calculate a frame, which might be lower than 1024 bytes
        var sliceTOSend; 
        for (var i=0; i<file.byteLength; i++) {
            if ( i+1024 > file.byteLength ) {
                sliceTOSend = file.byteLength - i;
            } else {
                sliceTOSend = 1024;
            }
            if (sliceTOSend == 0) {
                break;
            }
            socket.send(file.slice(i, i+sliceTOSend));
            i+= sliceTOSend -1;
        } // end algorithmn

        console.log("Connection closing...");
        socket.readystate = socket.CLOSING;
        socket.close();
    }

    // Error handler
    socket.onerror = function(e) {
        alert("Error! " + e.data);
        return;
    }

    // Handler for the server answers
    socket.onmessage = function(e) {
        console.log("Server says: "+e.data);
    }

    // Close handler
    socket.onclose = function(e) {
        console.log("Connection closed. Getting ready for new connections!");
        socket.readystate = socket.CLOSED;
        location.reload();
    }
}


/**
    ------------------------------------------------------------------------------------------------------------------------------
    Design functions
    ------------------------------------------------------------------------------------------------------------------------------
**/

/**
  *
  *  This function manipulates the css 'display' property and is managing the breadcrumb structure.
  *  TODO expand: Bug about filesystems structure with length greater than 3. Duplicating the folder link 
  *  Handles the GoBack link to the upper folder structure.
  *  The function is called with the path of the Folder.
  *
  **/

function viewFolderFiles (name) 
{
    currentPath = name; 
    var nameForBreadcrumb = name.split("/");
    var pathForGoBack = name.split("/");

    // delete all existing breadcrumbs
    $(".breadcrumb").each(function(){
            $("li").remove();
    });
            
    var dumpLast = pathForGoBack.pop();
    pathForGoBack = pathForGoBack.join("/");

    // this loop fills all breadcrumbs according to the current folder
    for (var i=0; i<nameForBreadcrumb.length; i++) {
        if (i == 0) {
            nameForBreadcrumb[0] = "Index";
            $(".breadcrumb").append("<li><a href=\"javascript:showRoot()\">"+nameForBreadcrumb[0]+"</a></li>");
            nameForBreadcrumb[0] = ".";
        } 
        else if (i == nameForBreadcrumb.length-1)  {
            $(".breadcrumb").append("<li class=\"active\">"+nameForBreadcrumb[i]+"</li>")
        } 
        else {
            $(".breadcrumb").append("<li><a href=\"javascript:viewFolderFiles('"+pathForGoBack+"')\">"+nameForBreadcrumb[i]+"</a></li>");
        }
    }

    var filesInFolders = $('tr');
        
    // this loop sets the visibility according to the current folder
    filesInFolders.each(function(){
        if ($(this).attr("data-parent") == name) {
            if ($(this).hasClass("folder")) {
                $(this).css("display", "table-row");
            }    
           $(this).css("display","table-row"); 
        } else {
           $(this).css("display", "none");
        }
    });
    
    if (pathForGoBack.length <= 1) {
        $("#goBack").html("<td><a href=\"javascript:showRoot()\">&lt;--  Go Back</a></td>");
    } else {
        $("#goBack").html("<td><a href=\"javascript:viewFolderFiles('"+pathForGoBack+"')\">&lt;--  Go Back</a></td>");
    }
    
    $("#goBack").css("display", "table-row");
}

/**
  *
  *  This function shows the Root Folder structure with it´s files. 
  *
  **/

function showRoot ()
{
    currentPath = ".";
    var files = $("tr");
    
    files.each(function(){
        if ($(this).attr("data-parent") == ".") {
            if ($(this).hasClass("folder")) {
                $(this).css("display", "table-row");
            }    

            $(this).css("display", "table-row");
        } else {
            $(this).css("display", "none");
        }
    });

    $("#goBack").css("display", "none");
    $(".breadcrumb").each(function(){
            $("#last").remove();
    });
    $(".active").remove();
}


/**
   ------------------------------------------------------------------------------------------------------------------------------
   Other functions 
   ------------------------------------------------------------------------------------------------------------------------------
 **/

// TODO expand with the new download attribute from HTML5 
function downloadFile (filePath)
{
    window.open(filePath, "_blank");;}
