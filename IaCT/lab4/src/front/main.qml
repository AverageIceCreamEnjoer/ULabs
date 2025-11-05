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
    width: 800
    height: 300
    minimumWidth: rootLayout.implicitWidth// + 30
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
        onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                openDialog.sourceFileInput.filePath = pathString;
                if (fileContentTA) {
                    fileContentTA.text = coder.readFileContent(pathString);
                    fileContentTA = null;
                }
            }
        }
        // Пользовательское свойство, чтобы диалог "знал", какое поле обновлять
        property FileInput sourceFileInput
        property StyledTextArea fileContentTA: null
    }

    FileDialog {
        id: saveDialog
        title: "Выберите файл для сохранения"
        fileMode: FileDialog.SaveFile // Позволяет вводить новое имя файла
        onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                saveDialog.sourceFileInput.filePath = pathString;
            }
        }
        property FileInput sourceFileInput
    }

    Item {
        id: contentContainer
        width: parent.width
        //height: rootLayout.implicitHeight
        anchors.fill: parent
        //Layout.fillHeight: true
        //Layout.fillWidth: true
        ScrollView {
            anchors.fill: parent
            height: parent.height
            ScrollBar.vertical.interactive: true
            //Layout.fillHeight: true
            width: parent.width
            clip: true
            //Layout.fillWidth: true
            GridLayout {
                id: rootLayout
                //Layout.fillWidth: true
                columns: 6
                anchors.fill: parent
                anchors.margins: 10
                anchors.centerIn: parent
                //Layout.leftMargin: 10
                //Layout.alignment: Qt.AlignHCenter
                width: parent.parent.width - 20
                FileInput {
                    id: encryptKey
                    Layout.columnSpan: 3
                    labelText: "Ключ:"
                    placeholderText: "Выберите файл с ключом шифра..."
                    onButtonClicked: {
                        openDialog.sourceFileInput = encryptKey;
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
                        openDialog.sourceFileInput = encryptInputPath;
                        openDialog.fileContentTA = encryptInputText;
                        openDialog.open();
                    }
                }
                FileInput {
                    id: encryptOutputPath
                    Layout.columnSpan: 3
                    labelText: "Выходной файл:"
                    placeholderText: "Выбрать, куда сохранить выходной файл..."
                    onButtonClicked: {
                        saveDialog.sourceFileInput = encryptOutputPath;
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
}
