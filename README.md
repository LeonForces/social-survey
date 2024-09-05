## Разработка приложения для хранения и обработки данных «Социалогический опрос»

Приложение для обработки данных социологического опроса. Основным требованием является достаточный объем вопросов (не менее 20), на которые подразумеваются различные виды ответа: 
* в виде числа,
* с единичным или множественным выбором из предложенных вариантов,
* либо в виде развернутого текста.

Количество хранимых заполненных форм достаточно велико (> 500’000 шт.). Функционал приложения обеспечивает:
* возможность поиска форм по различным критериям (минимум 5 различных критериев);
* статистическую обработку результатов с подсчетом абсолютных и относительных частот для каждого пункта, который могли выбрать участники опроса.

Реализована возможность добавления результата опроса, удаления результата опроса. Для демонстрации работы реализиван генератор ответов, выдающий случайным образом заполненные формы опроса (генерация реализована посредством паттерна “абстрактная фабрика”). Функционал обработки данных реализован таким образом, чтобы тип коллекции, в которой будут храниться ваши данные, являлся параметром. Обработку данных продемонстрирована с использованием std::unordered_map и собственной реализации динамического массива.
