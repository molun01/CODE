function showDialog() {
    alert("Android");
}

(function () {
    var timeEl = document.getElementById("time");
    timeEl.innerHTML = new Date();
})();

function toggleImage() {
    var image = document.getElementById("myImage");
    if (image.src.match("android1")) {
        image.src = "img/android2.png";
    } else {
        image.src = "img/android1.png";
    }
}