import pytest

@pytest.mark.parametrize("base, exponent, expected", [
    (2, 2, 4),
    (2, 3, 8),
    (1, 9, 0),  #Error case to check if it is failed
    (0, 9, 0),
    (2, -2, 0.25), 
    (-2, 3, -8),    
    (-2, 2, 4),     
    (0, 0, 1),     #Python treats 0^0 as 1 
    (10, 5, 100000) 
])
def test_power(base, exponent, expected):
    assert pow(base, exponent) == expected

if __name__ == "__main__":
    import sys
    sys.exit(pytest.main(["-v"]))
