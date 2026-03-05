#!/usr/bin/env python3

import paymentlib


def main() -> None:
    principal = 10000.0
    annual_rate_percent = 7.5
    months = 36

    monthly_payment = paymentlib.calculate_required_payment(
        principal,
        annual_rate_percent,
        months,
    )

    print(f"Principal: ${principal:,.2f}")
    print(f"APR: {annual_rate_percent:.2f}%")
    print(f"Term: {months} months")
    print(f"Required monthly payment: ${monthly_payment:,.2f}")


if __name__ == "__main__":
    main()
