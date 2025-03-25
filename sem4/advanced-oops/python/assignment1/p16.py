def create_stock_dict():
    n = int(input("Enter number of stocks: "))
    stock_dict = {}
    for _ in range(n):
        name = input("Enter stock name: ")
        price = int(input("Enter stock price: "))
        stock_dict[name] = price
    return stock_dict

def find_min_max(stock_dict):
    min_price = min(stock_dict.values())
    max_price = max(stock_dict.values())
    return min_price, max_price

def sort_by_price(stock_dict):
    return dict(sorted(stock_dict.items(), key=lambda x: x[1]))

def find_differences(dict1, dict2):
    only_in_first = set(dict1.keys()) - set(dict2.keys())
    price_mismatch = {k: (dict1[k], dict2[k]) for k in dict1 if k in dict2 and dict1[k] != dict2[k]}
    return only_in_first, price_mismatch

def remove_duplicates(stock_dict):
    seen_values = set()
    unique_dict = {}
    for k, v in stock_dict.items():
        if v not in seen_values:
            seen_values.add(v)
            unique_dict[k] = v
    return unique_dict

def group_by_price(stock_dict):
    grouped = {}
    for k, v in stock_dict.items():
        group = (v // 500) * 500
        if group not in grouped:
            grouped[group] = []
        grouped[group].append((k, v))
    return grouped

def find_item_by_price(stock_dict, price):
    return [k for k, v in stock_dict.items() if v == price]

def main():
    print("Enter first stock dictionary:")
    stock_dict1 = create_stock_dict()
    print("Enter second stock dictionary:")
    stock_dict2 = create_stock_dict()
    
    min_price, max_price = find_min_max(stock_dict1)
    print("Minimum price:", min_price)
    print("Maximum price:", max_price)
    
    sorted_dict1 = sort_by_price(stock_dict1)
    sorted_dict2 = sort_by_price(stock_dict2)
    print("Sorted first dictionary:", sorted_dict1)
    print("Sorted second dictionary:", sorted_dict2)
    
    only_in_first, price_mismatch = find_differences(stock_dict1, stock_dict2)
    print("Stocks only in first dictionary:", only_in_first)
    print("Stocks with mismatched prices:", price_mismatch)
    
    unique_dict1 = remove_duplicates(stock_dict1)
    print("First dictionary after removing duplicates:", unique_dict1)
    
    grouped_dict = group_by_price(stock_dict1)
    print("Grouped stocks by price (multiples of 500):", grouped_dict)
    
    items_800_dict1 = find_item_by_price(stock_dict1, 800)
    items_800_dict2 = find_item_by_price(stock_dict2, 800)
    print("Stocks with price 800 in first dictionary:", items_800_dict1)
    print("Stocks with price 800 in second dictionary:", items_800_dict2)

if __name__ == "__main__":
    main()
