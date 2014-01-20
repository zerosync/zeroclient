function viewFolderFiles (name) 
{
    $(".breadcrumb").append("<li class=\"active\">"+name+"</li>");
    
    var filesInFolders = $('tr');
        
    filesInFolders.each(function(){
        if ($(this).attr("parent-folder") == name) {
           $(this).css("display","table-row"); 
        } else {
            $(this).css("display", "none");
        }
    });
    $("#goBack").css("display", "table-row");
} 

function showRoot (){
    var rootFiles = $(".fromRoot");
    rootFiles.push($(".folder"));

    rootFiles.each(function(){
            $(this).css("display", "table-row");
    });

    var folderFiles = $(".notFromRoot");
    folderFiles.each(function(){
            $(this).css("display", "none");
    });
    $("#goBack").css("display", "none");
    $(".active").remove();
}
