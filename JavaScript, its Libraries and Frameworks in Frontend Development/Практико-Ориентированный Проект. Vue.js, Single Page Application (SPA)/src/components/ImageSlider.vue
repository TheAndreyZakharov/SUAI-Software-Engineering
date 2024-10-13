<template>
  <div class="image-slider-container">
    <div class="slider-header">
      <h2>Вдохновляющие идеи для вашего дома:</h2>
      <h2>Как могут выглядеть Умные розетки в интерьере</h2>
    </div>
    <div class="image-slider">
    <button @click="prevSlide" class="slider-btn prev-btn">&#60;</button>
    <div class="slides">
      <transition-group name="fade" tag="div">
        <img
          v-for="(image, index) in images"
          :key="image"
          :src="image"
          class="slide-image"
          :style="{ opacity: index === currentSlide ? 1 : 0 }"
        />
      </transition-group>
    </div>
    <button @click="nextSlide" class="slider-btn next-btn">&#62;</button>
  </div>
</div>
</template>

<script>
export default {
  name: 'ImageSlider',
  data() {
    return {
      currentSlide: 0,
      images: [
        require('@/assets/photo6.jpg'),
        require('@/assets/photo7.jpg'),
        require('@/assets/photo8.jpg'),
        require('@/assets/photo9.jpg'),
        require('@/assets/photo10.jpg'),
        require('@/assets/photo11.jpg'),
        require('@/assets/photo12.jpg'),
        require('@/assets/photo13.jpg'),
        require('@/assets/photo14.jpg'),
        require('@/assets/photo15.jpg')
        ]
    }
  },
  methods: {
    nextSlide() {
      this.currentSlide = (this.currentSlide + 1) % this.images.length;
    },
    prevSlide() {
      this.currentSlide = this.currentSlide - 1 < 0 ? this.images.length - 1 : this.currentSlide - 1;
    }
  }
};
</script>

<style scoped>

.image-slider-container {
  text-align: center; /* Центрирование текста */
  margin-bottom: 20px; /* Отступ перед слайдером */
}

.slider-header h2 {
  font-size: 24px; /* Размер шрифта для заголовка */
  color: #333; /* Цвет текста */
  margin: 20px 0; /* Вертикальные отступы */
}
.image-slider {
  width: 600px;
  height: 600px;
  position: relative;
  margin: auto;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: space-between; /* Распределение пространства */
}

@media (max-width: 800px) {
  .image-slider {
    width: 80%;
    min-height: 300px;
  }
}

@media (max-width: 550px) {
  .image-slider {
    width: 70%;
    min-height: 200px;
  }
}

.slides {
  width: 100%;
  height: 100%;
  display: flex; /* Использование Flexbox */
  justify-content: center;
  align-items: center;
  position: relative;
}

.slides img {
  max-width: 100%; /* Максимальная ширина изображения */
  max-height: 100%; /* Максимальная высота изображения */
  object-fit: contain; /* Это свойство гарантирует, что изображения полностью помещаются в контейнер без обрезки */
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%); /* Центрирование изображения */
  transition: opacity 0.5s ease;
}
/* Стили для анимации исчезновения и появления */
.fade-enter-active, .fade-leave-active {
  transition: opacity 0.5s ease;
}

.fade-enter, .fade-leave-to {
  opacity: 0;
}

/* Добавление промежуточного состояния для плавного перехода */
.fade-enter-to, .fade-leave {
  opacity: 1;
}

.slider-btn {
  background-color: #fff;
  border: 2px solid black;
  color: black;
  padding: 0px 10px;
  cursor: pointer;
  transition: background-color 0.3s, color 0.3s, transform 0.3s; /* Плавный переход для цвета, фона и трансформации */
  z-index: 10;
  font-size: 24px;
  margin: 0 10px; /* Добавление отступов для кнопок */
  border-radius: 10px; /* Закругление краев */

}

.slider-btn:hover {
  background-color: #ccc; /* Более темный цвет при наведении */
  transform: scale(1.15); /* Увеличение при наведении */
}



</style>