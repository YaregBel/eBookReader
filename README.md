# eBookExpress

Нашей задачей было создание приложения, направленного на чтение электронных книг, различных форматов, при этом предоставляя пользователю возможность настроить процесс чтения на удобную для него волну.

## Структура проекта

Проект имеет стандартную структуру для приложения основанного на C++, QML и Aurora OS.
- [ru.auroraos.eBooksReader.pro](https://github.com/YaregBel/eBookReader/blob/main/ru.auroraos.eBooksReader.pro) файл описывает структуру проекта для его сборки, используя утилиту для сборки приложения - qmake.
- [icons](https://github.com/YaregBel/eBookReader/tree/main/icons) директория, содержащая иконки приложений для различных разрешений экрана.
- [qml](https://github.com/YaregBel/eBookReader/tree/main/qml) директория, содержащая исходный код QML и ресурсы пользовательского интерфейса.
  - [cover](https://github.com/YaregBel/eBookReader/tree/main/qml/cover) директория, содержащая варианты, обложек приложения.
  - [icons](https://github.com/YaregBel/eBookReader/tree/main/qml/icons) директория, содержащая дополнительные иконки для интерфейса.
  - [pages](https://github.com/YaregBel/eBookReader/tree/main/qml/pages) директория, содержащая страницы приложения.
  - [ru.auroraos.eBooksReader.qml](https://github.com/YaregBel/eBookReader/tree/main/qml/ru.auroraos.eBooksReader.qml) файл, который представляет собой реализацию окна приложения.
- [rpm](https://github.com/YaregBel/eBookReader/tree/main/rpm) директория, содержащая настройка сборки rpm-пакета.
  - [ru.auroraos.eBooksReader.spec](https://github.com/YaregBel/eBookReader/blob/main/rpm/ru.auroraos.eBooksReader.spec) файл, использующийся инструментом rpmbuild
- [src](https://github.com/YaregBel/eBookReader/tree/main/src) директория, содержащая исходники C++ кода.
- [translations](https://github.com/YaregBel/eBookReader/tree/main/translations) директория содержит файлы перевода пользовательского интерфейса.
- [ru.auroraos.eBooksReader.desktop](https://github.com/YaregBel/eBookReader/blob/main/ru.auroraos.eBooksReader.desktop) файл, определяющий как файл будет отображаться и его параметры для запуска приложения.

## Совместимость

Проект совместим с версией Aurora 5.0.0.60-base и новее.

## Как работает

- При запуске приложения, подгружается страница __MainPage.qml__
- После полной загрузки страницы __MainPage.qml__, срабатывает метод __listFiles__, класса __FileReader__.
- После возвращается список файлов, расположенных в директории ~/Documents/ и уже исходя из длины этого списка, генерируется нужное количество записей, необходимых для отображения книг на книжной полке.
- Далее при долгом нажатии на запись, появляется выпадающее меню, в котором можно, выбрав пункт - "Открыть книгу", перейти на страницу __TextPage.qml__.
- Одновременно с открытием страницы, происходит считывание файла с книгой, по __индексу 0__ и вывод этой книги в элемент Text. При этом происходит обработка всех тегов и пагинация страниц.
- На странице __TextPage.qml__, пользователь может перелистывать страницы книги и увеличивать или уменьшать размер шрифта, а также выйти обратно, на главный экран, смахнув вправо или нажав на нужную для этого кнопку

## Скриншоты

![image](https://github.com/YaregBel/eBookReader/assets/90565494/7b399ad3-3519-4815-b408-7d731f662618)
![image](https://github.com/YaregBel/eBookReader/assets/90565494/fc602f87-a344-4093-9f9d-b74db16e3ab7)
![image](https://github.com/YaregBel/eBookReader/assets/90565494/0654e529-fef8-4ef4-a6c2-1fcbb930dd4b)
![image](https://github.com/YaregBel/eBookReader/assets/90565494/e281a949-909e-436f-8c7b-2b555dd61b6d)



