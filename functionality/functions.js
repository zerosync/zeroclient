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
