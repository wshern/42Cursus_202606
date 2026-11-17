def ft_harvest_total():
    day = 1
    total = 0
    while day <= 3:
        total += int(input(f"Day {day} harvest: "))
        day += 1
    print(f"Total harvest: {total}")
# ft_harvest_total()
