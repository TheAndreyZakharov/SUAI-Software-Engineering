<%@ page contentType="text/html; charset=UTF-8" %>
<!DOCTYPE html>
<html>
<meta charset="UTF-8">
<head>
    <title>Моя страница</title>
</head>
<body>

<style>
    .container {
        display: flex;
        justify-content: space-between;
        align-items: flex-start;
    }

    .form-container {
        width: 10%;
    }

    .sell-form-container {
        width: 90%;
    }

    .display-button {
        width: 15%;
        text-align: center;
        margin-top: 20px;
    }
    .sell-button {
        margin-top: 60px;
    }
</style>

<div class="container">
    <div class="form-container">
        <form action="/servlet" method="GET">
            <label for="stockName">Название акции:</label><br>
            <input type="text" id="stockName" name="stockName"><br>
            <label for="stockID">ID акции:</label><br>
            <input type="text" id="stockID" name="stockID" pattern="\d+" title="Please enter only numbers"><br>
            <label for="purchaseDate">Дата покупки:</label><br>
            <input type="date" id="purchaseDate" name="purchaseDate"><br><br>
            <input type="submit" value="Купить">
        </form>
    </div>
    <div class="sell-form-container">
        <form action="/servlet" method="POST">
            <label for="stockName">Название акции:</label><br>
            <input type="text" id="stockName" name="stockName"><br>
            <label for="stockID">ID акции:</label><br>
            <input type="text" id="stockID" name="stockID" pattern="\d+" title="Please enter only numbers"><br>
            <input class="sell-button" type="submit" value="Продать">
        </form>
    </div>
</div>
<div class="display-button">
    <form action="/servlet/display" method="GET">
        <input type="submit" value="Показать портфель акций">
    </form>
</div>

</body>
</html>
