document.addEventListener("DOMContentLoaded", function() {
    const images = [
        { url: "image1.jpg", link: "image1.jpg" },
        { url: "image2.jpg", link: "image2.jpg" },
        { url: "image3.jpg", link: "image3.jpg" }
    ];

    let currentImageIndex = 0;
    const slideImage = document.getElementById("slide-image");
    const slideLink = document.getElementById("slide-link");

    function updateSlide() {
        slideImage.src = images[currentImageIndex].url;
        slideLink.href = images[currentImageIndex].link;
        currentImageIndex = (currentImageIndex + 1) % images.length;
    }

    setInterval(updateSlide, 1000);
});
