// Импортируем необходимые модули QML
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Window

import MyComponents 1.0

// Импортируем наш C++ класс
import CipherDiagram 1.0

// Создаем главный объект - окно
ApplicationWindow {
    id: root
    //width: 800
    height: 600
    minimumWidth: rootLayout.implicitWidth * 2 + 30
    //minimumHeight: rootLayout.implicitHeight
    visible: true
    //Material.theme: Material.Light
    title: "Шифр Плейфера"

    // Создаем экземпляр нашего C++ объекта.
    // Теперь мы можем обращаться к нему по id: coder
    EncryptAlgorithms {
        id: coder
    }

    // Диалоги для выбора файлов
    FileDialog {
        id: openDialog
        title: "Выберите файл для шифрования"
        /*onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                openDialog.sourceFileInput.filePath = pathString;
            }
        }
        // Пользовательское свойство, чтобы диалог "знал", какое поле обновлять
        property FileInput sourceFileInput*/
    }

    FileDialog {
        id: saveDialog
        title: "Выберите файл для сохранения"
        fileMode: FileDialog.SaveFile // Позволяет вводить новое имя файла
        /*onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                saveDialog.sourceFileInput.filePath = pathString;
            }
        }
        property FileInput sourceFileInput*/
    }
    ScrollView {
        width: rootLayout.implicitWidth + 20
        Layout.fillHeight: true
        Layout.rightMargin: 10
        Layout.leftMargin: 10
        clip: true
        GridLayout {
            id: rootLayout
            columns: 6
            width: parent.width
            FileInput {
                id: encryptKey
                Layout.columnSpan: 3
                labelText: "Ключ:"
                placeholderText: "Выберите файл с ключом шифра..."
                onButtonClicked: {
                    openDialog.onAccepted = function() {
                        // Получаем путь к файлу (убираем "file://")
                        var pathString = openDialog.selectedFile.toString().substring(7);
                        encryptKey.filePath = pathString;
                    }
                    //openDialog.sourceFileInput = encodeKey;
                    openDialog.open();
                }
            }
            Button {
                id: encryptButton
                Layout.columnSpan: 3
                text: "Зашифровать собщение"
                onClicked: {
                    encryptOutputText.text = coder.encryptPlayfair(encryptKey.filePath, encryptInputText.text);
                    coder.saveContent(encryptOutputPath.filePath, encryptOutputText.text);
                }
            }
            FileInput {
                id: encryptInputPath
                Layout.columnSpan: 3
                labelText: "Входной файл:"
                placeholderText: "Выберите файл для шифрования..."
                onButtonClicked: {
                    openDialog.onAccepted = function() {
                        // Получаем путь к файлу (убираем "file://")
                        var pathString = openDialog.selectedFile.toString().substring(7);
                        encryptInputPath.filePath = pathString;
                        var content = coder.readFileContent(pathString);
                        encryptInputText.text = content;
                    }
                    //openDialog.sourceFileInput = encryptInputPath;
                    openDialog.open();
                }
            }
            FileInput {
                id: encryptOutputPath
                Layout.columnSpan: 3
                labelText: "Выходной файл:"
                placeholderText: "Выбрать, куда сохранить выходной файл..."
                onButtonClicked: {
                    saveDialog.onAccepted = function() {
                        // Получаем путь к файлу (убираем "file://")
                        var pathString = saveDialog.selectedFile.toString().substring(7);
                        encryptOutputPath.filePath = pathString;
                    }
                    //saveDialog.sourceFileInput = encryptOutputPath;
                    saveDialog.open();
                }
            }
            StyledTextArea {
                id: encryptInputText
                Layout.columnSpan: 3
                readOnly: false
                placeholderText: "Сообщение для шифрования..."
            }
            StyledTextArea {
                id: encryptOutputText
                Layout.columnSpan: 3
                readOnly: true
                placeholderText: "Результат шифрования..."
            }
            Label {
                id: statusLabel
                Layout.fillWidth: true
                Layout.topMargin: 15
                Layout.bottomMargin: 15
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
            }
        }
    }
}
