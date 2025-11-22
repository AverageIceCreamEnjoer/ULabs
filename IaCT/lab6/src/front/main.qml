// Импортируем необходимые модули QML
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Window

import MyComponents 1.0

// Импортируем наш C++ класс
import AdditiveGenerator 1.0

// Создаем главный объект - окно
ApplicationWindow {
    id: root
    width: 800
    height: 300
    maximumHeight: 800
    //minimumWidth: rootLayout.implicitWidth// + 30
    //minimumHeight: rootLayout.implicitHeight
    visible: true
    Material.theme: Material.Light
    title: "Аддитивный генератор псевдослучайных чисел"
    // Создаем экземпляр нашего C++ объекта.
    Generator {
        id: generator
    }

    // Диалоги для выбора файлов
    FileDialog {
        id: openDialog
        title: "Выберите файл с входными параметрами"
        onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                openDialog.sourceFileInput.filePath = pathString;
                if (fileContentTA) {
                    fileContentTA.text = generator.readFileContent(pathString);
                    fileContentTA = null;
                }
            }
        }
        // Пользовательское свойство, чтобы диалог "знал", какое поле обновлять
        property FileInput sourceFileInput
        property StyledTextArea fileContentTA: null
    }

    Item {
        anchors.fill: parent
        FileInput {
            id: generatorInputPath
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.margins: 15
            labelText: "Входной файл:"
            placeholderText: "Выберите файл с входными параметрами..."
            onButtonClicked: {
                openDialog.sourceFileInput = generatorInputPath;
                openDialog.fileContentTA = generatorInputText;
                openDialog.open();
            }
        }
        Button {
            id: generateButton
            anchors.top: parent.top
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.margins: 15
            text: "Сгенерировать последовательность"
            onClicked: {
                generatorOutputText.text = generator.generatePrime(generatorInputText.text);
            }
        }
        StyledTextArea {
            id: generatorInputText
            anchors.top: generatorInputPath.bottom
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 15
            readOnly: false
            placeholderText: "Параметры последовательности..."
        }
        StyledTextArea {
            id: generatorOutputText
            anchors.top: generatorInputPath.bottom
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 15
            readOnly: true
            placeholderText: "Сгенерированная последовательность..."
        }
    }
}
