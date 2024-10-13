<template>
  <div id="app">
    <AppNavbar/>
    <HomePage/>
    <SmartPlugInfo/>
    <ImageSlider/>
    <FeedbackForm/>
    <AppFooter/>
  </div>
</template>

<script>
import AppNavbar from './components/AppNavbar.vue'
import HomePage from './components/HomePage.vue'
import SmartPlugInfo from './components/SmartPlugInfo.vue'
import ImageSlider from './components/ImageSlider.vue'
import FeedbackForm from './components/FeedbackForm.vue'
import AppFooter from './components/AppFooter.vue'



export default {
  name: 'App',
  components: {
    AppNavbar,
    HomePage,
    SmartPlugInfo,
    ImageSlider,
    FeedbackForm,
    AppFooter

  }
}
</script>

<style>
/* Импорт глобальных стилей */
@import './assets/main.css';
</style>
