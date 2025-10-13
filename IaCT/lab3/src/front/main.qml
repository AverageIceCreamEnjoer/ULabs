// Импортируем необходимые модули QML
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Window
//import QtQuick.Controls.Material

// Импортируем наш C++ класс
import com.mycompany.coding 1.0

// Создаем главный объект - окно
ApplicationWindow {
    id: root
    //width: 600
    //height: 400
    minimumWidth: rootLayout.implicitWidth
    minimumHeight: rootLayout.implicitHeight
    visible: true
    //Material.theme: Material.Light
    title: "Кодирование алгоритмом Гильберта-Мура"

    // Создаем экземпляр нашего C++ объекта.
    // Теперь мы можем обращаться к нему по id: coder
    CodingAlgorithms {
        id: coder
    }

    // Диалоги для выбора файлов
    FileDialog {
        id: openDialog
        title: "Выберите файл для кодирования"
        onAccepted: {
            if (selectedFile) {
                // Преобразуем строку URL в локальный путь
                var pathString = selectedFile.toString();
                if (pathString.startsWith("file://")) {
                    pathString = pathString.substring(7); // Удаляем "file://"
                }
                openDialog.sourceTextField.text = pathString;
            }
        }
        // Пользовательское свойство, чтобы диалог "знал", какое поле обновлять
        property TextField sourceTextField
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
                saveDialog.sourceTextField.text = pathString;
            }
        }
        property TextField sourceTextField
    }

    // Главный контейнер
    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.margins: 10
        Layout.rightMargin: 30
        Layout.leftMargin: 30

        // --- Секция кодирования ---
        GroupBox {
            title: "Кодирование без проверки"
            Layout.fillWidth: true

            GridLayout {
                columns: 3
                width: parent.width

                Label {
                    text: "Входной файл:"
                }
                TextField {
                    id: encodeInputPath
                    Layout.fillWidth: true
                    placeholderText: "Выберите файл для кодирования..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        // Указываем диалогу, какое поле обновить
                        openDialog.sourceTextField = encodeInputPath;
                        openDialog.open();
                    }
                }

                Label {
                    text: "Выходной файл:"
                }
                TextField {
                    id: encodeOutputPath
                    Layout.fillWidth: true
                    placeholderText: "Выбрать, куда сохранить выходной файл..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        saveDialog.sourceTextField = encodeOutputPath;
                        saveDialog.open();
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10

            Button {
                text: "Кодировать"
                onClicked: {
                    var success = coder.encodeGilbertMoore(encodeInputPath.text, encodeOutputPath.text);
                    statusLabel.text = success ? "Успешно закодировано!" : "Кодирование завершилось с ошибкой. Смотрите консоль вывода для деталей.";
                    statusLabel.color = success ? "green" : "red";
                }
            }
            Button {
                text: "Декодировать"
                onClicked: {
                    var success = coder.decodeGilbertMoore(encodeInputPath.text, encodeOutputPath.text);
                    statusLabel.text = success ? "Успешно декодировано!" : "Декодирование завершилось с ошибкой. Смотрите консоль вывода для деталей.";
                    statusLabel.color = success ? "green" : "red";
                }
            }
        }

        GroupBox {
            title: "Проверка на четность"
            Layout.fillWidth: true
            Layout.topMargin: 15 // Небольшой отступ сверху

            GridLayout {
                columns: 3
                width: parent.width

                // Поля для кодирования
                Label {
                    text: "Входной файл:"
                }
                TextField {
                    id: parityInputPath
                    Layout.fillWidth: true
                    placeholderText: "Выбрать входной файл для чтения..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        openDialog.sourceTextField = parityInputPath;
                        openDialog.open();
                    }
                }

                Label {
                    text: "Выходной файл:"
                }
                TextField {
                    id: parityOutputPath
                    Layout.fillWidth: true
                    placeholderText: "Выбрать куда сохранить выходной файл..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        saveDialog.sourceTextField = parityOutputPath;
                        saveDialog.open();
                    }
                }
                Label {
                    text: "Лог ошибок:"
                    font.bold: true
                    Layout.topMargin: 10
                }
                TextArea {
                    id: parityErrorArea
                    Layout.fillWidth: true
                    Layout.minimumHeight: 80
                    readOnly: true
                    placeholderText: "Здесь будут отображаться ошибки декодирования..."
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10

            Button {
                text: "Кодирование с проверкой на четность"
                onClicked: {
                    var success = coder.encodeParity(parityInputPath.text, parityOutputPath.text);
                    statusLabel.text = success ? "Кодирование с проверкой на четность прошло успепшно!" : "Кодирование с проверкой на четность завершилось с ошибкой.";
                    statusLabel.color = success ? "green" : "red";
                }
            }
            Button {
                text: "Декодирование с проверкой на четность"
                onClicked: {
                    var errorLog = coder.decodeParity(parityInputPath.text, parityOutputPath.text);
                    parityErrorArea.text = errorLog;
                    statusLabel.text = errorLog != "false" ? "Декодирование с проверкой на четность прошло успешно!" : "Декодирование с проверкой на четность завершилось с ошибкой.";
                    statusLabel.color = errorLog != "false" ? "green" : "red";
                }
            }
        }

        // --- Статус бар ---
        Label {
            id: statusLabel
            Layout.fillWidth: true
            Layout.topMargin: 15
            Layout.bottomMargin: 15
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            text: "Готово"
        }
    }
}
