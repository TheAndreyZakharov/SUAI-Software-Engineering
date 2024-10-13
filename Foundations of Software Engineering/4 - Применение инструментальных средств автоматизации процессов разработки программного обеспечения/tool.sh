#!/bin/bash
# Исходный код утилиты для создания и управления systemd сервисами

# Функция для создания systemd сервиса из скрипта .sh
create_systemd_service_from_script() {
    local script_path=$1
    local service_name=$2
    local description=$3

    if [[ ! -f "$script_path" ]]; then
        echo "Ошибка: скрипт '$script_path' не найден."
        return 1
    fi

    if [[ -z "$service_name" ]]; then
        service_name=$(basename "$script_path" .sh)
    fi

    local service_file="/etc/systemd/system/$service_name.service"

    echo "[Unit]
Description=$description
After=network.target

[Service]
ExecStart=/bin/bash $script_path
Restart=always

[Install]
WantedBy=multi-user.target" > "$service_file"

    systemctl daemon-reload
    systemctl enable "$service_name"
    systemctl start "$service_name"

    echo "Сервис '$service_name' успешно создан и запущен."
}

# Функция для создания systemd сервиса из команды или службы
create_systemd_service_from_command() {
    local command=$1
    local service_name=$2
    local description=$3

    if [[ -z "$service_name" ]]; then
        service_name=${command// /_}
    fi

    local service_file="/etc/systemd/system/$service_name.service"

    echo "[Unit]
Description=$description
After=network.target

[Service]
ExecStart=$command
Restart=always

[Install]
WantedBy=multi-user.target" > "$service_file"

    systemctl daemon-reload
    systemctl enable "$service_name"
    systemctl start "$service_name"

    echo "Сервис '$service_name' успешно создан и запущен."
}

# Функция отображения справочной информации об использовании утилиты
show_usage_info() {
    echo "Использование: my_service_tool <команда> [опции]"
    echo "Команды:"
    echo "  create-from-script <путь_к_скрипту> [имя_сервиса] [описание] - Создает сервис из скрипта .sh"
    echo "  create-from-command <команда> [имя_сервиса] [описание] - Создает сервис из команды или службы"
    echo "  help - Отображает эту справку"
}

# Проверка наличия прав суперпользователя
if [[ $EUID -ne 0 ]]; then
    echo "Этот скрипт должен быть запущен с правами суперпользователя"
    exit 1
fi

# Основная логика скрипта
main() {
    if [[ $# -lt 1 ]]; then
        show_usage_info
        exit 1
    fi

    case "$1" in
        create-from-script)
            create_systemd_service_from_script "$2" "$3" "$4"
            ;;
        create-from-command)
            create_systemd_service_from_command "$2" "$3" "$4"
            ;;
        help)
            show_usage_info
            ;;
        *)
            echo "Неверная команда: $1"
            show_usage_info
            exit 1
            ;;
    esac
}

# Запуск основной функции с переданными аргументами
main "$@"
