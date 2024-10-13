<template>
  <hr>
  <div id="feedback" class="content-section">
    <h2>Обратная Связь</h2>
    <form @submit.prevent="submitForm">
      <div class="form-group">
        <label for="name">Имя:</label>
        <input type="text" id="name" v-model="formData.name">
      </div>
      <div class="form-group">
        <label for="email">Email:</label>
        <input type="email" id="email" v-model="formData.email">
      </div>
      <div class="form-group">
        <label for="message">Сообщение:</label>
        <textarea id="message" v-model="formData.message"></textarea>
      </div>
      <div class="message-container">
        <p v-if="errorMessage" class="error-message">{{ errorMessage }}</p>
        <p class="submitted-message" :class="{ active: submitted }">Спасибо за ваше сообщение!</p>
      </div>
      <button type="submit">Отправить</button>
    </form>
    <div v-if="showModal" class="modal-overlay" @click="closeModal">
      <div class="modal-content" @click.stop>
        <p>Ваше сообщение успешно отправлено!</p>
        <button @click="closeModal">Закрыть</button>
      </div>
  </div>
</div>
</template>

<script>
export default {
  name: 'FeedbackForm',
  data() {
    return {
      formData: {
        name: '',
        email: '',
        message: ''
      },
      submitted: false,
      errorMessage: '',
      showModal: false
    };
  },
  methods: {
    submitForm() {
      // Валидация формы
      if (!this.formData.name || !this.formData.email || !this.formData.message) {
        this.errorMessage = 'Пожалуйста, заполните все поля.';
        return;
      }

      if (!/\S+@\S+\.\S+/.test(this.formData.email)) {
        this.errorMessage = 'Пожалуйста, введите корректный адрес электронной почты.';
        return;
      }

      console.log('Отправлено:', this.formData);
      this.submitted = true;
      this.errorMessage = '';
      this.clearForm();

      this.showModal = true; // Открываем модальное окно

    },

    closeModal() {
    this.showModal = false;
  },


    clearForm() {
      this.formData.name = '';
      this.formData.email = '';
      this.formData.message = '';
    }
  }
}
</script>


<style scoped>


/* Стили для формы */
.content-section {
background-color: white; /* Белый фон для раздела */
padding: 0px;
border-radius: 15px; /* Закругленные углы */
box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5); /* Небольшая тень для эффекта "выпуклости" */
display: flex;
flex-direction: column;
align-items: center;
margin-bottom: 60px; /* Дополнительное место под формой */
margin: 20px; /* Отступ, чтобы отделить раздел от краев экрана */
position: relative; /* Для абсолютного позиционирования внутри */
padding-bottom: 100px; /* Дополнительный отступ снизу для сообщений */
}
.content-section ul {
list-style-type: circle; /* Стиль списка */
margin-left: 20px;
}
.form-group {
margin-bottom: 15px;
width: 100%;
max-width: 600px; /* Ограничение ширины */
}

label {
display: block;
margin-bottom: 5px;
text-align: left;
}

input, textarea {
width: 100%;
border: 1px solid #ccc;
border-radius: 4px;
box-sizing: border-box;
}

input {
padding: 8px;
margin-bottom: 10px;
}

textarea {
padding: 8px;
margin-bottom: 10px;
height: 150px; /* Увеличиваем высоту поля ввода сообщения */
width: 400px;
}

button {
padding: 10px 20px;
border: none;
border-radius: 4px;
background-color: #007bff;
color: white;
cursor: pointer;
transition: background-color 0.3s;
align-self: center; /* Выравнивание кнопки по центру */
}

button:hover {
background-color: #0056b3;
}

/* Стили для блоков сообщений */
.message-container {
  position: absolute;
  bottom: 10px; /* Положение в нижней части формы */
  left: 20px;
  right: 20px;
}

.error-message, .submitted-message {
  text-align: center;
  height: 20px;
}

.error-message {
  color: red;
}

.submitted-message {
  color: green;
  visibility: hidden;
}

.submitted-message.active, .error-message.active {
  visibility: visible;
}

/* Стили для модального окна */
.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
}

.modal-content {
  background-color: white;
  padding: 20px;
  border-radius: 10px;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5);
}

.modal-content p {
  margin: 0;
  margin-bottom: 20px;
}


</style>