# Тестирование

В данном разделе содержатся файлы, которые подвергаются тесту.

> Возможно, стоит сделать разеделение на Windows/Linux

## Работа с mtrace

При старте программы запускается функция `mtrace()`
Она позволяет найти все места, с утечкой памяти

### Как пользоваться

Необходимо запускать скрипт `build.sh`
Данный скрипт содержит в себе экспортируемую переменную для работы mtrace

```bash
TRACE_FILE=trace
export MALLOC_TRACE=$PWD/$TRACE_FILE
```

> Это все можно изменить по своему желанию, однако стоит помнить, файлы логов не стоит
> отправлять на сервер, т.к. это потенциальная угроза!

Скрипт скомпилирует код с флагом `-g` для сохранения информации о отладки и запустит программу.
Далее, в текущей категории должен появиться файл `trace`.
Чтобы его прочитать используем следующую команду:

```bash
mtrace ./main trace
```

, где:

- ./main - имя скопилированной программы
- trace - файл с выходной информации об утечках