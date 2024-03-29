# ContentSearcher

Программа для поиска документов.

Читайте этот текст в иных языках: [English](README.md), [Русский](README.ru.md)

_(Комментарии внутри кода пока написаны на русском.)_

_**ПРИМЕЧАНИЕ:** Данный текст ещё в процессе написания._

---

## Описание проекта

Локальный поисковый движок.

Данный проект был выполнен как итоговая работа по прохождению курса по C++ от SkillBox.

---

## Стек используемых технологий

- язык программирования **С++**
- среда разработки **CLion**
- среда разработки **VSCode**
- средство автоматизации сборки **CMake - Ninja**
- компилятор **GCC v12.2.1**
- операционная система **Manjaro KDE (Arch Linux)**
	- (без включения ОС-специальных библиотек)
- контроль версий **Git - GitHub**
- библиотека для работы с json-файлами **nlohmann_json**
- библиотека управления тестами **google_test**

---

## Инструкция к компиляции

1. Удостоверьтесь в присутствии и актуальности следующих файлов:
	- папка [include](include)
	- папка [src](src)
	- [CMakeLists.txt](CMakeLists.txt)
	- [VersionConfig.h.in](VersionConfig.h.in)
2. Откройте директорию в любой среде разработки **С++**, поддерживающей **CMake - Ninja**;
3. Запустите сборку проекта **ContentSearcher**, описанного в [CMakeLists.txt](CMakeLists.txt);
4. Перейдите в папку **src**, что должна была сгенерироваться внутри Вашей сборочной папки;
5. Скопируйте/переместите исполняемый файл **ContentSearcher** в любую удобную Вам директорию.

---

## Инструкция к использованию

1. Откройте папку [examples](examples);
2. Скопируйте файлы [config.json](examples/config.json) и [requests.json](examples/requests.json) в одну директорию с Вашим исполняемым файлом **ContentSearcher**;
3. Откройте Ваш конфигурационный файл **config.json**:
	- уточните предельное количество ответов на один запрос в поле **_"max_responses"_**,
	- перечислите пути к файлам, по которым будет совершаться поиск в поле **_"files"_** (пути, задаваемые формулами не принимаются, один путь - один файл);
4. Откройте Ваш файл с запросами **requests.json**:
	- перечислите поисковые запросы в поле **_"requests"_**;
5. Запустите Ваш исполняемый файл **ContentSearcher**:
	- рекомендуется запускать в терминале/оболочке, иначе вы не будете уведомлены о возможных ошибках,
	- в случае возникновения фатальной ошибки прочтите её описание и совершите соответствующие контрмеры;
6. Ознакомьтесь с результатами поиска при получении сообщения о записи файла **answers.json** в той же директории.

Программа проводит инвертированную индексацию слов в каждом указанном документе и выводит в качестве ответа номера документов (соответствующих позициям предоставленнго списка) в порядке релевантности, посчитанной с помощью суммы вхождений искомых слов в каждый отдельный документ. 

_**ВНИМАНИЕ:** Документ рассматривается как часть ответа, даже если в нём присутствуют не все искомые слова. Будьте осторожны с союзами и иными распространёнными или короткими словами в своих запросах._

Вывод в терминал:
- **[MESSAGE]** - сообщение, обозначающее этап работы программы;
- **[WARNING]** - предупреждение о возникновении нефатальной ошибки;
- **[ERROR]** - фатальная ошибка, экстренно закрывающая программу.

### При повторном использовании начинайте с шага #3.

_**ВНИМАНИЕ:** Новый **answers.json** всегда перезаписывает старый._
