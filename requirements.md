# Требования

## Функциональные требования

### Алгоритмы для анализа графов

- Поддержка заявленных алгоритмов для поиска кратчайших путей, работы с потоками и паросочетаниями
- Возможность обнаружения отрицательных циклов и других особенностей графов

### Взаимодействие с библиотекой
- Поддержка чтения и записи графов в различных форматах (GraphML, GML, TGF)
- Вывод результатов работы алгоритмов в удобном для пользователя формате

### Обработка ошибок
- Гарантия корректности результатов для различных входных данных
- Обработка некорректных входных данных (например, неверно заданные веса, несуществующие вершины)

## Нефункциональные требования

### Производительность
- Оптимизация алгоритмов для работы с большими графами
- Использование эффективных структур данных для хранения графов
- Время работы алгоритма должно соотноситься с указанной асимптотикой и входными данными

### Расширяемость
- Архитектура не должна мешать добавлению новых алгоритмов
- Возможность добавления новых форматов описания графов без изменения существующих

### Пользовательский интерфейс
- Интуитивно понятный API для вызова алгоритмов
- Возможность настройки параметров алгоритмов


### Совместимость
- Поддержка работы на всех основных операционных системах: Linux, Mac, Windows.
- Система должна быть совместима с компиляторами gcc и clang версии C++20 и выше.


## Правила приемки
 - Все алгоритмы реализованы и протестированы
 - 90% покрытие кода модульными тестами
 - Все модульные тесты завершаются успешно
 - Модульные тесты проверяют все функциональные требования
 - Нефункциональные требования выполняются
   - Тесты выполняются за прогнозируемое время, в зависимости от заявленной асимптотики, что показывают бенчмарки
 - Документация позволяет полноценно использовать библиотеку
 - Библиотека успешно собирается и работает под заявленными ОС и компиляторами