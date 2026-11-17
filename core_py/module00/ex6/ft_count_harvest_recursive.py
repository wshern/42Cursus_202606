def count(days):
    if days == 0:
        return
    count(days - 1)
    print("Days", days)


def ft_count_harvest_recursive():
    days = int(input("Days until harvest: "))
    count(days)
    print("Harvest time!")
# ft_count_harvest_recursive()
