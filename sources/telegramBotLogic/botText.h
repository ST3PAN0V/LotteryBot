#include "../lotteryLogic/lottery.h"

static std::string menuMainTEXT;
static std::string menuTypedTicketTEXT;
static std::string menuTicketsTEXT;
static std::string userJoinTEXT;
static std::string newUserJoinTEXT;
static std::string adminJoinTEXT;
static std::string trySetLotteryIntervalSuccesTEXT;
static std::string trySetLotteryIntervalFailedTEXT;
static std::string nearestLotteryTEXT;
static std::string uncorrectinputTEXT;
static std::string sameNumbersTEXT;
static std::string uncorrectInputTEXT;
static std::string uncorrectNumbersTEXT;
static std::string wrongCountNumbersTEXT;

std::string GetNormalString(const std::vector<std::string>& vecStr) {
    std::string returnObject = "";
    if (returnObject != "") return returnObject;
    for (const auto& str : vecStr) {
        returnObject += str;
        returnObject += '\n';
    }
    return returnObject;
}

const std::vector<std::string> menuMainEDITABLE = {
    "\t<b><u>Главное меню</u></b>\n",
    "Тут ты можешь выбрать то, что тебе надо!"
};

const std::vector<std::string> menuTicketsEDITABLE = {
    "\t<b><u>Меню билетов</u></b>\n",
    "Чтобы купить билет напиши следующую команду:\n",
    "<b>/buyTicket (номера слотов)</b>\n",
    "<i><b>Подсказка:</b> номера слотов вводи в скобках и разделяй запятой, не добавляя лишних пробелов и символов.</i>",
    "<i><b>Пример:</b></i> /buyTicket (35,40,4,17,22,10,39,2)\n",
    "Доступно всего <i><u>19</u></i> билетов.\n",
    "попытки|цена в рублях",
    " 6   | 50",
    " 7   | 350",
    " 8   | 1 400",
    " 9   | 4 200",
    " 10 | 10 500",
    " 11 | 23 100",
    " 12 | 46 200",
    " 13 | 85 800",
    " 14 | 150 150",
    " 15 | 250 250",
    " 16 | 400 400",
    " 17 | 618 800",
    " 18 | 928 200",
    " 19 | 1 356 600"
};

const std::vector<std::string> userJoinEDITABLE = {
    "О! Я узнал тебя, ты же тот самый <b><i>{}</i></b>!\n",
    "Пиши <b>/menu</b> чтобы перейти в гланое меню"
};

const std::vector<std::string> newUserJoinEDITABLE = {
    "Ты новенький? Я тебя запомнил!",
    "Теперь ты можешь купить билет! пиши <b>/menu</b>"
};

const std::vector<std::string> adminJoinEDITABLE = {
    "Привет {}!\n",
    "Комманды админа:\n",
    "*Установить интервал создания и розыгрыша лоттерей*",
    "/SetLotteryInterval YYYY-MM-DD HH:MM:SS"
};

const std::vector<std::string> trySetLotteryIntervalSuccesEDITABLE = {
    "Лоттерея создана!\n",
    "<b>Дата:</b> <i>{}</i>",
    "<b>Время:</b> <i>{}</i>"
};

const std::vector<std::string> trySetLotteryIntervalFailedEDITABLE = {
    "Неверный формат ввода. Ты рукожоп :(",
    "Вот пример:\n",
    "<b>/SetLotteryInterval 0000-00-00 03:00:00</b>"
};

const std::vector<std::string> nearestLotteryEDITABLE = {
    "Ближайшая лоттерея будет <b>{}</b> в <b>{}</b>"
};

const std::vector<std::string> menuTypedTicketEDITABLE = {
    "\t<b><u>Покупка билета</u></b>\n",
    "Отлично! Вот твой билет:\n",
    "<b>Количество попыток:</b> {}",
    "<b>Выбранные номера:</b> {}",
    "<b>Цена билета:</b> {} рублей\n",
    "Если все верно, то можно спокойно покупать билет, иначе отменяй"
};

const std::vector<std::string> sameNumbersEDITABLE = {
    "\t<b><u>Ошибка!</u></b>\n",
    "<u>{}</u>\n",
    "<i>Вы ввели 2 одинаковых числа!</i>"
};

const std::vector<std::string> uncorrectInputEDITABLE = {
    "\t<b><u>Ошибка!</u></b>\n",
    "<u>{}</u>\n",
    "<i>Некорректный ввод! У вас есть лишние символы или пробелы.</i>"
};

const std::vector<std::string> uncorrectNumbersEDITABLE = {
    "\t<b><u>Ошибка!</u></b>\n",
    "<u>{}</u>\n",
    "<i>Числа должны быть от 1 до 45</i>"
};

const std::vector<std::string> wrongCountNumbersEDITABLE = {
    "\t<b><u>Ошибка!</u></b>\n",
    "<u>{}</u>\n",
    "<i>Чисел должно быть от 6 до 19</i>"
};


void CacheTEXTstrings() {
    menuMainTEXT = move(GetNormalString(menuMainEDITABLE));
    menuTicketsTEXT = move(GetNormalString(menuTicketsEDITABLE));
    userJoinTEXT = move(GetNormalString(userJoinEDITABLE));
    newUserJoinTEXT = move(GetNormalString(userJoinEDITABLE));
    adminJoinTEXT = move(GetNormalString(adminJoinEDITABLE));
    trySetLotteryIntervalSuccesTEXT = move(GetNormalString(trySetLotteryIntervalSuccesEDITABLE));
    trySetLotteryIntervalFailedTEXT = move(GetNormalString(trySetLotteryIntervalFailedEDITABLE));
    nearestLotteryTEXT = move(GetNormalString(nearestLotteryEDITABLE));
    menuTypedTicketTEXT = move(GetNormalString(menuTypedTicketEDITABLE));
    sameNumbersTEXT = move(GetNormalString(sameNumbersEDITABLE));
    uncorrectInputTEXT = move(GetNormalString(uncorrectInputEDITABLE));
    uncorrectNumbersTEXT = move(GetNormalString(uncorrectNumbersEDITABLE));
    wrongCountNumbersTEXT = move(GetNormalString(wrongCountNumbersEDITABLE));
}

