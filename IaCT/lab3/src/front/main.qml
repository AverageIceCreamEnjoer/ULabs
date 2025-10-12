// Импортируем необходимые модули QML
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Material

// Импортируем наш C++ класс
import com.mycompany.coding 1.0

// Создаем главный объект - окно
Window {
    id: root
    width: 600
    height: 400
    visible: true
    Material.theme: Material.Light
    title: "Кодирование алгоритмом Гильберта-Мура"

    // Создаем экземпляр нашего C++ объекта.
    // Теперь мы можем обращаться к нему по id: coder
    GilbertMooreCoder {
        id: coder
    }

    // Диалоги для выбора файлов
    FileDialog {
        id: openDialog
        title: "Выберите файл для кодирования"
        onAccepted: {
            // Эта функция будет вызвана, когда мы выберем файл
            // Мы передадим путь в текстовое поле, которое его вызвало
            openDialog.sourceTextField.text = selectedFile;
        }
        // Пользовательское свойство, чтобы диалог "знал", какое поле обновлять
        property TextField sourceTextField
    }

    FileDialog {
        id: saveDialog
        title: "Выберите файл для сохранения"
        fileMode: FileDialog.SaveFile // Позволяет вводить новое имя файла
        onAccepted: {
            saveDialog.sourceTextField.text = selectedFile;
        }
        property TextField sourceTextField
    }

    // Главный контейнер
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        // --- Секция кодирования ---
        GroupBox {
            title: "Кодирование"
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

        Button {
            id: encodeButton
            text: "Кодировать"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
            onClicked: {
                // Вызываем C++ метод!
                var success = coder.encodeFile(encodeInputPath.text, encodeOutputPath.text);
                if (success) {
                    statusLabel.text = "Успешно закодировано!";
                    statusLabel.color = "green";
                } else {
                    statusLabel.text = "Кодирование завершилось с ошибкой. Смотрите консоль вывода для деталей.";
                    statusLabel.color = "red";
                }
            }
        }

        // --- Секция декодирования ---
        GroupBox {
            title: "Декодирование"
            Layout.fillWidth: true
            Layout.topMargin: 20

            GridLayout {
                columns: 3
                width: parent.width

                Label {
                    text: "Входной файл:"
                }
                TextField {
                    id: decodeInputPath
                    Layout.fillWidth: true
                    placeholderText: "Выбрать файл для декодирования..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        openDialog.sourceTextField = decodeInputPath;
                        openDialog.open();
                    }
                }

                Label {
                    text: "Выходной файл:"
                }
                TextField {
                    id: decodeOutputPath
                    Layout.fillWidth: true
                    placeholderText: "Выбрать куда сохранить выходной файл..."
                }
                Button {
                    text: "Выбрать..."
                    onClicked: {
                        saveDialog.sourceTextField = decodeOutputPath;
                        saveDialog.open();
                    }
                }
            }
        }

        Button {
            id: decodeButton
            text: "Декодировать"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
            onClicked: {
                // Вызываем C++ метод!
                var success = coder.decodeFile(decodeInputPath.text, decodeOutputPath.text);
                if (success) {
                    statusLabel.text = "Успешно декодировано!";
                    statusLabel.color = "green";
                } else {
                    statusLabel.text = "Декодирование завершилось с ошибкой. Смотрите консоль вывода для деталей.";
                    statusLabel.color = "red";
                }
            }
        }

        // --- Статус бар ---
        Label {
            id: statusLabel
            Layout.fillWidth: true
            Layout.topMargin: 15
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            text: "Готово"
        }
    }
}
