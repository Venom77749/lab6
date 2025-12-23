#pragma once

/// <summary>
/// Класс пистолета, выполняющего одиночные выстрелы.
/// </summary>
class Pistol {
protected:
    int ammo; ///< Текущее количество патронов

public:
    /// <summary>
    /// Создает пистолет с заданным количеством патронов (по умолчанию 5).
    /// </summary>
    /// <param name="initialAmmo">Начальное количество патронов</param>
    Pistol(int initialAmmo = 5);
    /// <summary>
    /// Делает один выстрел: "Бах!", если есть патроны, иначе "Клац!".
    /// </summary>
    virtual void shoot();
    /// <summary>
    /// Возвращает количество оставшихся патронов.
    /// </summary>
    int getAmmo() const;
    /// <summary>
    /// Виртуальный деструктор для корректной работы наследников.
    /// </summary>
    virtual ~Pistol() = default;
};

/// <summary>
/// Класс автомата — наследник Pistol, стреляет очередями.
/// </summary>
class Automatic : public Pistol {
private:
    int rateOfFire;  ///< Скорострельность (выстрелов в секунду)
    int maxAmmo;     ///< Вместимость магазина

public:
    /// <summary>
    /// Конструктор по умолчанию: 30 патронов, скорострельность 30.
    /// </summary>
    Automatic();
    /// <summary>
    /// Конструктор с заданной вместимостью, скорострельность = половина вместимости.
    /// </summary>
    /// <param name="maxCapacity">Максимальное количество патронов</param>
    Automatic(int maxCapacity);
    /// <summary>
    /// Конструктор с заданной вместимостью и скорострельностью.
    /// </summary>
    /// <param name="maxCapacity">Максимальное количество патронов</param>
    /// <param name="fireRate">Скорострельность (выстрелов в секунду)</param>
    Automatic(int maxCapacity, int fireRate);

    /// <summary>
    /// Возвращает скорострельность автомата.
    /// </summary>
    int getRateOfFire() const;
    /// <summary>
    /// Делает очередь из rateOfFire выстрелов или пока не закончатся патроны.
    /// </summary>
    void shoot() override;
    /// <summary>
    /// Стреляет указанное число секунд: seconds * rateOfFire выстрелов
    /// или до опустошения магазина.
    /// </summary>
    /// <param name="seconds">Время стрельбы в секундах</param>
    void shootForSeconds(int seconds);
};