Pops - это официальный эмулятор PlayStation (PSX) для Sony PSP. Не зря я потратил прилично времени на знакомство с устройством PSP, попробуем как-нибудь применить эти знания.

Pops представляет собой 2 модуля: pops.prx и popsman.prx (менеджер). В pops.prx находится сам эмулятор, менеджер - это обвеска.

Зачем ломать? Интересно выяснить работу некоторых недокументированных регистров PSX при эмуляции BIOS, интересно посмотреть как эмулируется GTE и пр.
Как будем ломать: Pops 100% низкоуровневый эмулятор, который ничем не отличается от остальных подобных эмуляторов, то есть берём инструкцию, интерпретируем её (скорее всего), всё железо эмулируется средствами PSP. В состав pops.prx входит кастомный BIOS для PSX.

Пока не понятно есть ли что-то ценное в popsman.prx, так что его пока не трогаем. MD5 хеш моей версии pops.prx: 151bf8250ea0eb61988e00fbd452b463

Первым делом вырежем BIOS и попробуем его сэмулировать на обычных эмуляторах.

**Кастомный Pops BIOS.**<br>
Первым делом нужно найти сигнатуру - строку "Sony Computer Entertainment  CEX-3000... by K.S." или как то так. Находится эта строка в районе 0x06BC30. Выше как известно находится стартовый код загрузки BIOS. Находим это место и вырезаем 512 Кб (или сколько получится, потому что BIOS кастомный и возможно кастрированный). Получаем начало BIOS из дизассемблированного pops.prx, полученного с помощью утилиты prxtool:<br>
<pre><code>	0x0006BA8C: 0x3C080013 '...&lt;' - lui        $t0, 0x13<br>
	0x0006BA90: 0x3508243F '?$.5' - ori        $t0, $t0, 0x243F<br>
	0x0006BA94: 0x3C011F80 '...&lt;' - lui        $at, 0x1F80<br>
	0x0006BA98: 0xAC281010 '..(.' - sw         $t0, 4112($at)<br>
	0x0006BA9C: 0x00000000 '....' - nop        <br>
	0x0006BAA0: 0x24080B88 '...$' - li         $t0, 2952<br>
	0x0006BAA4: 0x3C011F80 '...&lt;' - lui        $at, 0x1F80<br>
	0x0006BAA8: 0xAC281060 '`.(.' - sw         $t0, 4192($at)<br>
	0x0006BAAC: 0x00000000 '....' - nop        <br>
</code></pre>

Начало типичного BIOS :) Так как коды PSP CPU и <a href='https://code.google.com/p/pops-gte/source/detail?r=3000'>R3000</a> совпадают, prxtool выдал сразу читаемый текст BIOS.<br>
Это место соответствует смещению в файле: 0x06BB2C.<br>
Версия BIOS походу дела соответствует SCPH-1001 (наиболее популярная версия, используемая во фриварных эмуляторах), так как дата BIOS, записанная перед сигнатурой:<br>
<pre><code>	0x0006BB8C: 0x19951204 '....' - 1995.12.04<br>
	0x0006BB90: 0x00000003 '....' - <br>
</code></pre>

Запустить сграбленный BIOS мне удалось на ePSXe:<br>
<br>
<img src='http://psxdev.narod.ru/images/pops_bios.png'>

psX вылетает с ошибкой, на остальных эмуляторах запускать не пробовал.<br>
<br>
Как я и думал из BIOS вырезали белую заставку (её время занимает заставка загрузки приложения PSP) и SHELL (менеджер карт памяти и CD-проигрыватель). Оставили только минимальную часть - загрузчик ядра PSX Kernel и CD-лоадер.<br>
<br>
Скачать Pops BIOS: <a href='http://psxdev.narod.ru/download/PopsBIOS.zip'>http://psxdev.narod.ru/download/PopsBIOS.zip</a>

<hr />

<h2>Внутри Pops.</h2>

Теперь нам как-то нужно собственно похачить Pops. Последовательно реверсить pops.prx от module_start будет непосильной задачей, притом что не известны названия многих импортируемых вызовов PSP из других модулей.<br>
<br>
Чтобы добраться до внутренностей эмулятора можно предположить что он работает как все остальные интерпретируемые эмуляторы.<br>
То есть у него есть модуль интерпретации инструкций <a href='https://code.google.com/p/pops-gte/source/detail?r=3000'>R3000</a>, обработчик доступа к хардварным регистрам, модули эмуляции GPU/SPU и прочих аппаратных узлов PSX.<br>
<br>
Соответственно нужно за что-то "зацепиться", а так как prxtool даёт в листинге перекрёстные ссылки, то у нас есть прекрасная возможность найти процедуры эмуляции вплоть до главной петли (или как обычно в модулях PSP - до главного потока модуля).<br>
<br>
Попробуем зацепиться за обработку доступа к аппаратным регистрам PSX:<br>
0x1F801000-0x1F80xxxx - HARDWARE I/O<br>
Список всех документированных регистров PSX можно найти тут: <a href='http://psxdev.narod.ru/docs/memlayout.htm'>http://psxdev.narod.ru/docs/memlayout.htm</a>
Кстати в адресном пространстве PSP этот диапазон никак не используется.<br>
<br>
Нужно найти в листинге упоминание 0x1f80, исключая область PSX BIOS (которая тоже дизассемблируется prxtool):<br>
<br>
<b>sub_00001030:</b>
<pre><code>	0x000010A0: 0x3C0F1F80 '...&lt;' - lui        $t7, 0x1F80<br>
<br>
	0x00001128: 0x3C061F80 '...&lt;' - lui        $a2, 0x1F80<br>
<br>
	0x000011B0: 0x3C031F80 '...&lt;' - lui        $v1, 0x1F80<br>
<br>
	0x000011C4: 0x3C0D1F80 '...&lt;' - lui        $t5, 0x1F80<br>
	0x000011C8: 0x3C091F80 '...&lt;' - lui        $t1, 0x1F80<br>
<br>
	0x000011D8: 0x3C0B1F80 '...&lt;' - lui        $t3, 0x1F80<br>
</code></pre>

<b>sub_000012BC:</b>
<pre><code>	0x000012BC: 0x3C031F80 '...&lt;' - lui        $v1, 0x1F80<br>
<br>
	0x000012E4: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
<br>
	0x000012FC: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
<br>
	.......<br>
<br>
	0x0000AE14: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000AE2C: 0x34441070 'p.D4' - ori        $a0, $v0, 0x1070	INTC<br>
<br>
	0x0000B434: 0x3C051F80 '...&lt;' - lui        $a1, 0x1F80<br>
	0x0000B43C: 0x34A410E0 '...4' - ori        $a0, $a1, 0x10E0	DMA GPU OT (канал 6)<br>
<br>
	0x0000B478: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000B484: 0x344410F0 '..D4' - ori        $a0, $v0, 0x10F0	DMA INTC (управление DMAC)<br>
<br>
	0x0000B4B4: 0x3C071F80 '...&lt;' - lui        $a3, 0x1F80<br>
	0x0000B4BC: 0x34E31080 '...4' - ori        $v1, $a3, 0x1080	DMA MDEC (канал 0)<br>
<br>
	0x0000BF0C: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000BF24: 0x34441100 '..D4' - ori        $a0, $v0, 0x1100	ROOT COUNTERS<br>
<br>
	0x0000C3B0: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000C3C8: 0x34441810 '..D4' - ori        $a0, $v0, 0x1810	GPU<br>
<br>
	0x0000C60C: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000C624: 0x34441040 '@.D4' - ori        $a0, $v0, 0x1040	SIO<br>
<br>
	0x0000F018: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x0000F030: 0x34441820 ' .D4' - ori        $a0, $v0, 0x1820	MDEC<br>
<br>
	0x00010A1C: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x00010A40: 0x34441800 '..D4' - ori        $a0, $v0, 0x1800	CDROM<br>
<br>
	0x00026C38: 0x3C051F80 '...&lt;' - lui        $a1, 0x1F80<br>
	0x00026C58: 0x3C021F80 '...&lt;' - lui        $v0, 0x1F80<br>
	0x00026C70: 0x34441C00 '..D4' - ori        $a0, $v0, 0x1C00	SPU<br>
</code></pre>

Как видно таких областей совсем немного, причём если вначале по контексту некоторые куски кода напоминают выбор условия (видимо там и находится обработчик доступа к регистрам), то последующие вхождения напоминают непосредственно обработчики аппаратных узлов. Дополнительно я пометил обозначения устройств PSX, на которые ссылаются куски кода по контексту.<br>
<br>
Дизассемблированный листинг pops.prx без PSX BIOS (6.5 MB): <a href='http://psxdev.narod.ru/download/pops.txt'>http://psxdev.narod.ru/download/pops.txt</a>

<hr />

<h2>Работа с памятью 1.</h2>

Напомню карту физической памяти PSX:<br>
<ul><li>0x00000000-0x001FFFFF - RAM<br>
</li><li>0x1F000000-0x1F7FFFFF - память устройства, подсоединенного к параллельному порту (PIO)<br>
</li><li>0x1F800000-0x1F8003FF - Scratch (кэш данных)<br>
</li><li>0x1F801000-0x1F80???? - регистры аппаратуры<br>
</li><li>0x1FC00000-0x1FC7FFFF - ROM<br>
</li><li>0x1FFE0130 - недокументированный регистр.</li></ul>

Очердь за разбором кода, где упоминается 0x1f80.<br>
<br>
Первый кусок - это процедура для чтения памяти:<br>
<br>
<pre><code>u8 rombios[512*1024] = { .... } ; // тут находится кастомный ROM BIOS Pops<br>
<br>
// read_type: 0 - lb, 1 - lh, 2 - lw, 3 - read 0, 4 - lbu, 5 - lhu<br>
sub_106C:<br>
u32 ReadMemory (u32 address, int read_type)<br>
{<br>
	address &amp;= 0x1fffffff;	// обрезать старшие 3 бита (трансляция адреса, у PSX CPU нет MMU)<br>
<br>
	if ( (address-0x1fc00000) &lt; 0x80000 ) {	// Прочитать область ROM BIOS<br>
		void *ptr = rombios + address &amp; 0x7ffff;<br>
<br>
		switch ( read_type )<br>
		{<br>
			case 0: return *(s8 *)ptr;	// lb<br>
			case 1: return *(s16 *)ptr;	// lh<br>
			case 2: return *(s32 *)ptr;	// lw<br>
			case 4: return *(u8 *)ptr;	// lbu<br>
			case 5: return *(u16 *)ptr;	// lhu<br>
		}<br>
<br>
	}<br>
	else {	// остальная память<br>
<br>
		if ( address == 0x1f802030 || address == 0x1f802040 ) 	// отладочные регистры<br>
		{<br>
			if (read_type &lt; 3) return 0xffffffff;	// lb, lh и lw<br>
			else if (read_type == 4 ) return 0xff;	// lbu<br>
			else return 0xffff;	// lhu<br>
		}<br>
<br>
		if ( address &gt; 0x1f802040 )	// недокументированный регистр 0x1ffe0130. Его значение хранится в переменной.<br>
		{<br>
			if ( address == 0x1ffe0130 ) return [0x0011198C];<br>
		}<br>
<br>
		if ( (address - 0x1f000000) &lt; 0x800000 ) return 0;	// PIO (устройство не подсоединено)<br>
<br>
		GenException? ( 7, 0 );	// Скорее всего 7 это код исключения : DBE Bus error on Data load.<br>
<br>
		if (read_type &lt; 3) return 0xffffffff;	// lb, lh и lw<br>
		else if (read_type == 4 ) return 0xff;	// lbu<br>
		else return 0xffff;	// lhu<br>
	}<br>
<br>
}<br>
</code></pre>
<i>исходник представляет собой псевдокод на Си.</i>

Комментарии:<br>
<br>
- Трансляция адреса происходит просто: обрезанием 3х старших битов. Точно также делает и реальный PSX CPU, потому что в нём отсутствует блок трансляции адресов (MMU).<br>
- При попытке доступа к неиспользуемым диапазонам памяти возвращается 0xff и вызывается исключение DBE (#7). Я ещё не разбирал процедуру генерации исключения, но очевидно что Pops умеет это делать (в отличии от всех известных фриварных эмуляторов).<br>
- При попытке чтения памяти устройства PIO возвращается 0.<br>
- Значение недокументированного регистра 0xFFFE0130 хранится в переменной, так что Pops его где-то использует ещё.<br>
- В процедуре чтения упоминаются отладочные регистры 0x1f802030 и 0x1f802040, но никак не используются. Попытка их чтения не вызывает исключения DBE, но возвращается 0xff (как будто память не используется).<br>
- В этой процедуре не происходит обработка чтения Scrath pad буфера и доступа к хардварным регистрам. Наверное проверка на доступ к ним производится в другом месте.<br>
- Чтение из RAM также не обрабатывается, видимо тоже находится в другом месте.<br>
<br>
<hr />

<h2>Работа с памятью 2.</h2>

Второй кусок более простой, но от этого не менее интересный. Тут происходит типичная инициализация "заглушек" на неиспользуемые регистры, для этого используется функция установки хука:<br>
<br>
<pre><code>// Содержит в себе обработчик чтения/записи в регистр.<br>
typedef struct HookCB {<br>
         u32 (*readCB)(u32 addr, int read_type);<br>
         void (*writeCB)(u32 addr, u32 value, int write_type);<br>
} HookCB;<br>
</code></pre>

Сама таблица хуков располагается в памяти PSP по адресу 0x10000.<br>
<br>
<pre><code>sub_1018:<br>
void InstallHardwareHooks ( u32 address, int length, u32 (*readcb)(u32 addr, int read_type), void (*writecb)(u32 addr, u32 value, int write_type) )<br>
{<br>
	if (readcb == NULL) readcb = defaultReadHook;<br>
	<br>
	if (writecb == NULL) writecb = defaultWriteHook;<br>
<br>
	int cur = address / 8;<br>
	int amount = length / 8;<br>
<br>
	HookCB * ptr = address - 0x1f7f0000;	// по адресам 0x10000 ... располагается таблица хуков для обработки HW регистров.<br>
	int end = cur + amount;<br>
<br>
	do {<br>
		cur++;<br>
		ptr.readCB = readcb;<br>
		ptr.writeCB = writecb;<br>
		ptr++;<br>
	} while ( cur != end );<br>
}<br>
</code></pre>
Пустышки (используются, если не указан обработчик чтения или записи регистра):<br>
<br>
<b>u32 defaultReadHook ( u32 address, int read_type ) :</b>
<pre><code>	0x00001320: 0x3C020000 '...&lt;' - lui        $v0, 0x0<br>
	0x00001324: 0x7CA228C4 '.(.|' - ins        $v0, $a1, 3, 3<br>
	0x00001328: 0x24421338 '8.B$' - addiu      $v0, $v0, 4920<br>
	0x0000132C: 0x3C010001 '...&lt;' - lui        $at, 0x1<br>
	0x00001330: 0x00400008 '..@.' - jr         $v0<br>
	0x00001334: 0x7C815804 '.X.|' - ins        $at, $a0, 0, 12<br>
<br>
	0x00001338: 0x03E00008 '....' - jr         $ra<br>
	0x0000133C: 0x80222000 '. ".' - lb         $v0, 8192($at)		// lb<br>
	0x00001340: 0x03E00008 '....' - jr         $ra<br>
	0x00001344: 0x84222000 '. ".' - lh         $v0, 8192($at)		// lh<br>
	0x00001348: 0x03E00008 '....' - jr         $ra<br>
	0x0000134C: 0x8C222000 '. ".' - lw         $v0, 8192($at)		// lw<br>
	0x00001350: 0x03E00008 '....' - jr         $ra<br>
	0x00001354: 0x24020000 '...$' - li         $v0, 0			// return 0<br>
	0x00001358: 0x03E00008 '....' - jr         $ra<br>
	0x0000135C: 0x90222000 '. ".' - lbu        $v0, 8192($at)		// lbu<br>
	0x00001360: 0x03E00008 '....' - jr         $ra<br>
	0x00001364: 0x94222000 '. ".' - lhu        $v0, 8192($at)		// lhu<br>
	0x00001368: 0x03E00008 '....' - jr         $ra<br>
	0x0000136C: 0x00001021 '!...' - move       $v0, $zr			// return 0<br>
</code></pre>

<b>void defaultWriteHook ( u32 address, u32 value, int write_type ) :</b>
<pre><code>	0x00001370: 0x3C020000 '...&lt;' - lui        $v0, 0x0<br>
	0x00001374: 0x7CC220C4 '. .|' - ins        $v0, $a2, 3, 2<br>
	0x00001378: 0x24421388 '..B$' - addiu      $v0, $v0, 5000<br>
	0x0000137C: 0x3C010001 '...&lt;' - lui        $at, 0x1<br>
	0x00001380: 0x00400008 '..@.' - jr         $v0<br>
	0x00001384: 0x7C815804 '.X.|' - ins        $at, $a0, 0, 12<br>
<br>
	0x00001388: 0x03E00008 '....' - jr         $ra<br>
	0x0000138C: 0xA0252000 '. %.' - sb         $a1, 8192($at)		// sb<br>
	0x00001390: 0x03E00008 '....' - jr         $ra<br>
	0x00001394: 0xA4252000 '. %.' - sh         $a1, 8192($at)		// sh<br>
	0x00001398: 0x03E00008 '....' - jr         $ra<br>
	0x0000139C: 0xAC252000 '. %.' - sw         $a1, 8192($at)		// sw<br>
	0x000013A0: 0x03E00008 '....' - jr         $ra<br>
	0x000013A4: 0x00000000 '....' - nop        				// dummy<br>
</code></pre>

Ну и сама функция инициализации "пустых" обработчиков для HW регистров:<br>
<br>
<pre><code>sub_12BC:<br>
void InitHardwareHooks ()<br>
{<br>
	InstallHardwareHooks ( 0x1f801000, 0x1000, ReadMemory, WriteMemory );<br>
	InstallHardwareHooks ( 0x1f801060, 16, NULL, NULL );<br>
	InstallHardwareHooks ( 0x1f801000, 64, NULL, NULL );<br>
}<br>
</code></pre>
Как видно функция вначале устанавливает стандартные обработчики ReadMemory / WriteMemory для всех регистров (при попытке доступа будет сгенерировано исключение DBE), потом устанавливает "пустышки" для чтения/записи неиспользуемых регистров PSX :<br>
0x1f801060 - 0x1f801070<br>
0x1f801000 - 0x1f801040<br>
чтобы при доступе к ним не возникало исключения DBE.<br>
<br>
Логично предположить что остальные участки кода, которые я пометил красным, устанавливают хуки для обработки остальных регистров, а вызов хука производится при интерпретации инструкций чтения/записи.<br>
<br>
<hr />

<h2>GTE.</h2>

Не найдя способа получить обработчик инструкций LB/LH/LW я решил покопать процедуру GenException. Я думал что это процедура генерации исключения, но оказалось что это не так. Разбор приводить не буду, там не всё понятно, но совершенно случайно я натолкнулся на операцию <b>var & 0x3f</b> и ссылку на следующую таблицу:<br>
<br>
<pre><code>(0x0002CBD8):<br>
	0x00001010 0x0000DEFC 0x00001010 0x00001010 0x00001010 0x00001010 0x0000E58C 0x00001010<br>
	0x00001010 0x00001010 0x00001010 0x00001010 0x00000FE4 0x00001010 0x00001010 0x00001010<br>
	0x0000D37C 0x0000E7FC 0x00000F00 0x0000D678 0x0000E668 0x00001010 0x0000D7B8 0x00001010<br>
	0x00001010 0x00001010 0x00001010 0x0000D9DC 0x0000D5A4 0x00001010 0x0000DCB0 0x00001010<br>
	0x0000DD94 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010<br>
	0x00000F60 0x0000D4A8 0x0000E958 0x00001010 0x00001010 0x0000E5D0 0x0000E618 0x00001010<br>
	0x0000E36C 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010 0x00001010<br>
	0x00001010 0x00001010 0x00001010 0x00001010 0x00001010 0x00000F8C 0x00000FB8 0x0000DAF0<br>
</code></pre>

хорошенько присмотрелся к ней и понял что мне дико повезло :lol:<br>
<br>
<pre><code>void (*psxCP2[64])() = {<br>
	psxBASIC, gteRTPS , psxNULL , psxNULL, psxNULL, psxNULL , gteNCLIP, psxNULL, // 00<br>
	psxNULL , psxNULL , psxNULL , psxNULL, gteOP  , psxNULL , psxNULL , psxNULL, // 08<br>
	gteDPCS , gteINTPL, gteMVMVA, gteNCDS, gteCDP , psxNULL , gteNCDT , psxNULL, // 10<br>
	psxNULL , psxNULL , psxNULL , gteNCCS, gteCC  , psxNULL , gteNCS  , psxNULL, // 18<br>
	gteNCT  , psxNULL , psxNULL , psxNULL, psxNULL, psxNULL , psxNULL , psxNULL, // 20<br>
	gteSQR  , gteDCPL , gteDPCT , psxNULL, psxNULL, gteAVSZ3, gteAVSZ4, psxNULL, // 28 <br>
	gteRTPT , psxNULL , psxNULL , psxNULL, psxNULL, psxNULL , psxNULL , psxNULL, // 30<br>
	psxNULL , psxNULL , psxNULL , psxNULL, psxNULL, gteGPF  , gteGPL  , gteNCCT  // 38<br>
};<br>
</code></pre>

Это таблица опкодов GTE.<br>
<br>
<hr />

After that pops-gte project was launched on Google Code.