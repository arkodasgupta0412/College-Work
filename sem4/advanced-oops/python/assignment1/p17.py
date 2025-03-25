def flatten_dict(d, parent_key='', sep='.'):
    flat_dict = {}
    
    def recurse(t, key):
        if isinstance(t, dict):
            for k, v in t.items():
                recurse(v, f"{key}{sep}{k}" if key else k)
        elif isinstance(t, list):
            for i, v in enumerate(t):
                recurse(v, f"{key}{sep}{i}")
        else:
            flat_dict[key] = t
    
    recurse(d, parent_key)
    return flat_dict

nested = {
    'fullname': 'Alessandra',
    'age': 41,
    'phone-numbers': ['+447421234567', '+447423456789'],
    'residence': {
        'address': {
            'first-line': 'Alexandra Rd',
            'second-line': '',
        },
        'zip': 'N8 0PP',
        'city': 'London',
        'country': 'UK',
    },
}

flattened = flatten_dict(nested)
print(flattened)
