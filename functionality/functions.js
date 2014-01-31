/**
    -----------------------------------------------------------------------------------------------------------------------------
    WebSocket functions
    -----------------------------------------------------------------------------------------------------------------------------
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

function sendFile (file, name)
{
    window.alert("File:"+ file);
    socket = connectToZSSocket();
                            
    socket.onopen = function() {
        socket.readystate = socket.OPEN;
        var puf = new ArrayBuffer(7+name.length);
        alert("Bufferlänge: "+(7+name.length))
        var dataView = new DataView(puf);
      
        alert("size: " +file.byteLength); 
        // This functions send an initializing command 'ZSF' for ZeroSync File
        // It´s for the server to know, that a file is incoming
        dataView.setUint8(0, 'Z'.charCodeAt(0));
        dataView.setUint8(1, 'S'.charCodeAt(0));
        dataView.setUint8(2, 'F'.charCodeAt(0));

        dataView.setUint32(3, file.byteLength);
        for (var y=0; y<name.length; y++) {
            dataView.setUint8(y+7, name.charCodeAt(y));
        }
        alert(dataView.getUint32(3));
        socket.send(puf); //send command with length of the file´s bytes
        
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
        }
    }

    socket.onerror = function(e) {
        alert("Error! " + e.data);
        return;
    }

    socket.onmessage = function(e) {
        console.log("Server says: "+e.data);
    }
}

function connectToZSSocket ()
{
    if ("WebSocket" in window) {
        var socket = new WebSocket("ws://localhost:1234/*");
        socket.readystate = socket.CONNECTING;
        
        return socket; 
    } else {
        window.alert("ERROR: Sorry, your browser doesn´t support websockets. You may not use functions, like delete or upload.");
    }
}

/**
    ------------------------------------------------------------------------------------------------------------------------------
    Design functions
    ------------------------------------------------------------------------------------------------------------------------------
**/
function viewFolderFiles (name) 
{ 
    var nameForBreadcrumb = name.split("/");
    var pathForGoBack = name.split("/");

    $(".breadcrumb").each(function(){
            $("li").remove();
    });
            
    var dumpLast = pathForGoBack.pop();
    pathForGoBack = pathForGoBack.join("/");

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
            $(".breadcrumb").append("<li id=\"last\"><a href=\"javascript:viewFolderFiles('"+pathForGoBack+"')\">"+nameForBreadcrumb[i]+"</a></li>");
        }
    }

    var filesInFolders = $('tr');
        
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

function showRoot ()
{
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
