class Plant:
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float
    ) -> None:
        self.name: str = name
        self.height: float = height
        self.days: int = days
        self.grow_rate: float = grow_rate

    def show(self) -> None:
        print(f"{self.name}: {round(self.height, 1)}cm, {self.days} days old")

    def grow(self) -> None:
        self.height += self.grow_rate

    def age(self) -> None:
        self.days += 1

    def sim_growth(self) -> None:
        self.grow()
        self.age()
        self.show()


def main() -> None:
    rose = Plant("Rose", 25.0, 30, 0.8)
    init_height = rose.height
    sim_days = 7
    print("=== Garden Plant Growth ===")
    rose.show()
    for i in range(1, (sim_days + 1)):
        print(f"=== Day {i} ===")
        rose.sim_growth()
    print(f"Growth this week: {round(rose.height - init_height, 1)}cm")


if __name__ == "__main__":
    main()
