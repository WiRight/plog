# PLog

## How to use

Just include a lib

```c
#include "plog.h"
```

And in your code write following:

```c
plogInit(); // Initialize component

infoLog("Log Worked!"); // Say something in log!

plogDestroy(); // Destroy component
```
Thats is it!

#### Log types

- **infoLog** : Some info
- **assertLog** : Some info
- **warningLog** : Some info
- **debugLog** : Some info

#### Features

You can change log format!
But remember, you can't change count parameters

By default time format is "_DAY_._MONTH_._YEAR_ *HOURS*:*MINUTES*:*SECONDS*"
By default log format is "[_[timeFormat]_]  [**LOG_TYPE**] {_fileName_} {_functionName_} {_line_}: **log message**"
