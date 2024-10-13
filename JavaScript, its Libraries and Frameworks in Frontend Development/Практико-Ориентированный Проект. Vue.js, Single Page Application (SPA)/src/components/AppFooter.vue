<template>
  <footer class="app-footer">
    <!-- Содержимое футера -->
    <p>&copy; {{ currentYear }} SmartRozetki. Все права защищены.</p>
  </footer>
</template>

<script>
export default {
  name: 'AppFooter',
  data() {
    return {
      currentYear: new Date().getFullYear()
    };
  }
}
</script>

<style scoped>
.app-footer {
  background-color: #333; /* Темный фон */
  color: white; /* Белый цвет текста */
  text-align: center; /* Выравнивание текста по центру */
  padding: 20px 0; /* Вертикальный отступ */
  position: relative;
  bottom: 0;
  width: 100%;
  border-top-left-radius: 20px; /* Закругление левого верхнего угла */
  border-top-right-radius: 20px; /* Закругление правого верхнего угла */
  box-shadow: 0 -5px 15px rgba(0, 0, 0, 0.5); /* Тень для добавления глубины */
  font-family: 'Arial', sans-serif; /* Шрифт */
}

/* Стиль для текста в футере */
.app-footer p {
  margin: 0; /* Убрать стандартный отступ у параграфа */
  font-size: 1.2em; /* Увеличить размер шрифта */
  font-weight: 500; /* Полужирное начертание для лучшей видимости */
  letter-spacing: 1px; /* Расстояние между буквами для улучшения читаемости */
}

/* Адаптивные стили */
@media (max-width: 800px) {
  .app-footer {
    font-size: 0.9em; /* Меньший размер шрифта на мобильных устройствах */
    padding: 15px 0; /* Меньший отступ на мобильных устройствах */
  }
}
</style>

