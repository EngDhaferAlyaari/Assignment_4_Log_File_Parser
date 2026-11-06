# Assignment 4 - Log File Parser

**Student:** Eng. Dhafer Alyaari

## English
A simple C program that reads a log file and searches for a word such as `FAILED` or `404`.
It shows the matching lines with their numbers and counts the total alerts.

**Run:**
```cmd
log_parser.exe security.log FAILED
```

**Example output:**
```text
File: security.log
Keyword: FAILED

Line 2: 2026-11-06 08:12:13 FAILED Login attempt from 192.168.1.20
Line 5: 2026-11-06 08:17:20 FAILED Password for user guest
Line 8: 2026-11-06 08:25:30 FAILED Login attempt from 192.168.1.21

Total alerts: 3
```

To search for `404`, use `log_parser.exe security.log 404`.
You can also open `Run_Test.bat` on Windows to try both searches.

## العربية
برنامج بسيط بلغة C يقرأ ملف السجلات ويبحث عن كلمة مثل `FAILED` أو `404`.
يعرض السطور المطابقة مع أرقامها، ثم يطبع إجمالي عدد التنبيهات.

**طريقة التشغيل:**
```cmd
log_parser.exe security.log FAILED
```

**مثال النتيجة:** المثال أعلاه يوضح العثور على **3 تنبيهات** في السطور **2 و5 و8**.
وللبحث عن `404` استخدم الأمر `log_parser.exe security.log 404` وستظهر **نتيجتان**.

## Files / الملفات
- `log_parser.c` - C source code / الكود المصدري
- `log_parser.exe` - Windows program / برنامج ويندوز
- `security.log` - Sample log / سجل للتجربة
- `Run_Test.bat` - Run both examples on Windows / تشغيل المثالين
- `Example_Output.txt` - Actual test output / نتائج الاختبار الفعلية

**Note / ملاحظة:** The search is case-sensitive, and each matching line is counted once. / البحث يميّز بين الأحرف الكبيرة والصغيرة، ويُحسب السطر المطابق مرة واحدة.
