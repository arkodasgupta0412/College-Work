discount = {"Monday":10, "Tuesday":5, "Wednesday":15, "Thursday":5, "Friday":10, "Saturday":15, "Sunday":20}

print("Weekdays\n")
for day, dsc in discount.items():
    print("Today is", day.upper(),"!")
    print("Discount offered:", dsc, "%")
    print("\n")