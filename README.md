# Dive into UnrealBuildTool

Привет!  
Я - Tools programer. Чаще тулы пишу, чем изучаю, но иногда изучание "фауны" инструентов в той или иной сфере, которые уже существуют, может приятно удивить.Более того, это может сэкономить разработчикам и пользователям уйму времени, бизнесу - деньги, а мир останется без ещё одного, заново изобретённого велосипеда.  
Переходя от общего к частному, я хочу подробней остановиться на изучении возможностей инструмента `UnrealBuildTool`, который поставляется вместе с движком `Unreal Engine 4`. Говоря о движке `UE4`, нельза не упомянуть о тех тулах, которые живут и взаимодействуют между собой. Работая в редакторе `UE4` вы так или иначе запускаете различные самостоятельные инструменты, которые поставляются вместе с движком, такие как `UnrealBuildTool`, `UnrealVersionSelector`, `UnrealLightmass` и многие другие, и даже можете и не знать о них. Исходные коды всех этих инструментов вы можете найти в оффициальном репозитории движка на github от Epic Games. 

Итак, предлагаю поближе познакомиться с `UnrealBuildTool`, понять, что это за зверь и с чем его едят.

## Description

`UnrealBuildTool` (сокр. `UBT`) - это консольное приложение, написанное на C# (.Net Core), с помощью которого `UnrealEditor` генерирует проектные файлы для различных IDE, запускает процесс запаковки и сборки проекта и многое другое.  


## Зависимости 

Помимо различных пространств имен из dotNet Core, `UBT` ссылается на dll библиотеку `DotNETUtilities`, которая так же есть в оффициальном репозитории. В этой библиотеке описано очень много вспомогательных классов для взаимодействия с файловой системой различных ОС, для парсинга параметров командной строки и пр. 

Сам `UBT` управляется скриптами и обращается к скриптам по пути:
> UnrealEngine/Engine/Build/BatchFiles/

Поэтому и запуск `UnrealBuildTool.exe` должен производиться из этой директории из командной строки:
> cd %path_to_engine%/Engine/Build/BatchFiles/  
> ../../Binaries/

**На исполняемый файл `UBT` ссылаются следующие вспомогательные скрипты**:
* UnrealEngine\Engine\Build\BatchFiles\Build:
    * Windows: `UnrealEngine\Engine\Build\BatchFiles\Build.bat`
    * Linux: `UnrealEngine\Engine\Build\BatchFiles\Linux\Build.sh`
    * Mac: 
        * `UnrealEngine\Engine\Build\BatchFiles\Mac\Build.sh`
        * `UnrealEngine\Engine\Build\BatchFiles\Mac\XcodeBuild.sh`
* `UnrealEngine\Engine\Build\BatchFiles\Clean.bat`
* UnrealEngine\Engine\Build\BatchFiles\GenerateProjectFiles:
    * Windows: `UnrealEngine\Engine\Build\BatchFiles\GenerateProjectFiles.bat`
    * Linux: `UnrealEngine\Engine\Build\BatchFiles\Linux\GenerateProjectFiles.sh`
    * Mac: `UnrealEngine\Engine\Build\BatchFiles\Mac\GenerateProjectFiles.sh`
* `UnrealEngine\Engine\Build\BatchFiles\MakeAndInstallSSHKey.bat`

**Исполняем файл `UBT`, запускает следующие скрипты:**
* UnrealEngine/Engine/Build/BatchFiles/FixDependencyFiles:
    * Windows: `UnrealEngine/Engine/Build/BatchFiles/FixDependencyFiles.bat`
    * Linux: `UnrealEngine/Engine/Build/BatchFiles/Linux/FixDependencyFiles.sh`
    * Mac: `UnrealEngine/Engine/Build/BatchFiles/Mac/FixDependencyFiles.sh`

## Main features

Попробую описание основных возможностей сделать максимально удобным и универсилизированным. Постараюсь описать это в следующем формате:
* Feature
    * Описание
    * Формат команды
    * Параметры
    * Вызов через `BatchFiles`
    * Пример
    * Результат

### Generating project files

#### Описание (Generating project files)

Каждый программист любит свою "экосистему", свою IDE, свои тулчейны и тулы. `UBT` предоставляет нам возможность генерации UE4 пректов для разных популчярных IDE. Напиример, если вы не адепт Visual Studio, или условия работы в компании не позволяют использовать Community версию, или вас очень напрягает этот тяжеловес, то вы запросто можете сгенерировать себе проект для VS Code, для QT Creator, для Rider for UE, для CLion или другой IDE.
    
#### Формат команды (Generating project files)

> 