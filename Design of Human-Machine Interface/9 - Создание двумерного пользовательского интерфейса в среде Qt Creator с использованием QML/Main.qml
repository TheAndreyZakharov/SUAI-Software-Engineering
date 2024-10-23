import QtQuick
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Захаров Андрей 4133К"

    // Example of using various controls
    Column {
        spacing: 20
        anchors.centerIn: parent

        Button {
            text: "Нажми меня"
            onClicked: console.log("Кнопка нажата!")
        }

        CheckBox {
            text: "Отметь меня"
            onCheckedChanged: console.log("Отметка: ", checked)
        }

        TextField {
            placeholderText: "Введите текст здесь..."
        }

        Slider {
            from: 0
            to: 100
            value: 50
            onValueChanged: console.log("Значение ползунка: ", value)
        }

        // Добавим новый элемент - текстовое поле и флажок
        Text {
            text: "Это текстовое поле"
            font.pointSize: 20
            color: "blue"
        }

        RadioButton {
            text: "Выберите меня"
            onClicked: console.log("Радио кнопка выбрана")
        }

        ComboBox {
            model: ListModel {
                ListElement { name: "Опция 1" }
                ListElement { name: "Опция 2" }
                ListElement { name: "Опция 3" }
            }
            onCurrentIndexChanged: console.log("Выбрана опция: ", currentIndex)
        }
    }
}
