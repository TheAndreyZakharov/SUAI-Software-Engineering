<template>
  <nav class="app-navbar">
    <div class="navbar-content">
      <!-- Логотип -->
      <div class="navbar-logo">
        <a href="#home-page" class="logo-link"> <!-- Добавляем класс для ссылки -->
          <img src="@/assets/logo.png" alt="Логотип" class="logo-image"> <!-- Добавляем класс для изображения -->
        </a>
      </div> 

      <!-- Меню -->
      <ul>
        <li><a href="#home-page">Главная Страница</a></li>
        <li><a href="#smart-plug-info">Подробная Информация</a></li>
        <li><a href="#feedback">Обратная Связь</a></li>
      </ul>
    </div>
  </nav>
</template>


<script>
export default {
  name: 'AppNavbar'
}
</script>

<style scoped>
body, html {
  margin: 0;
  padding: 0;
  width: 100%;
  height: 100%;
}

.app-navbar {
  background-color: #333;
  z-index: 1000;
  width: 100%;
  position: relative; /* Фиксированное позиционирование */
  top: 0; /* Устранение отступа от верха страницы */
  left: 0;
  z-index: 1000; /* Убедиться, что шапка всегда наверху */
  box-shadow: 0 5px 15px rgba(0, 0, 0, 0.5); /* Тень для добавления глубины */
  padding: 10px 0; /* Вертикальные отступы */
  border-bottom-left-radius: 20px; /* Закругление нижнего левого угла */
  border-bottom-right-radius: 20px; /* Закругление нижнего правого угла */
}

.navbar-content {
  display: flex;
  flex-direction: column;
  align-items: center;
  padding: 20px 0; /* Отступ сверху и снизу внутри шапки */
}

.navbar-logo img {
  height: 50px; /* Высота логотипа */
  margin-bottom: 20px; /* Отступ от логотипа до меню */
}

.app-navbar ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  display: flex;
  justify-content: center;
}

.app-navbar li {
  margin: 0 10px;
}

.app-navbar li a {
  display: block;
  color: white;
  text-align: center;
  padding: 8px 12px;
  text-decoration: none;
  transition: background-color 0.3s, color 0.3s, transform 0.3s; /* Плавный переход для цвета, фона и трансформации */
  border-radius: 10px; /* Закругление углов */
  border: 1px solid black; /* Тонкая черная обводка */

}

.app-navbar li a:hover {
  background-color: #ddd;
  color: black;
  transform: scale(1.15); /* Увеличение при наведении */
}
@media (max-width: 800px) {
  .app-navbar ul {
    flex-direction: column; /* Ставим элементы навигации вертикально */
    align-items: center;
  }
  .app-navbar {
    height: auto; /* или задайте фиксированную высоту, если она известна */
  }
  .app-navbar li {
    margin: 5px 0; /* Увеличиваем вертикальные отступы между элементами навигации */
  }

  .content-section {
    padding: 15px; /* Уменьшаем отступы в основных секциях */
    padding-top: 120px; /* Увеличенный отступ, когда меню вертикальное */
  }
}
/* Стили для анимации логотипа */
.logo-link {
  display: inline-block; /* Делаем ссылку блочно-строчным элементом */
  transition: transform 0.3s ease; /* Плавный переход для трансформации */
}

.logo-link:hover {
  transform: scale(1.15); /* Увеличение при наведении */
}

.logo-image {
  height: 50px; /* Высота логотипа */
  /* Другие стили для изображения */
}


</style>
