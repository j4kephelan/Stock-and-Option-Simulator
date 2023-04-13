#include "trading.hpp"


double Pricer::norm_cdf(double x) {
    return (1.0 + std::erf(x / std::sqrt(2.0))) / 2.0;
}

std::pair<double, double> Pricer::black_scholes_primer(const Stock& stock) {
    double stock_price = stock.underlying_price;
    double strike_price = stock.strike_price;
    double time_to_expiry = stock.expiration_time;
    double risk_free_rate = stock.interest_rate;
    double implied_volatility = stock.volatility;

    double d1 = (std::log(stock_price / strike_price) + (risk_free_rate +
     (implied_volatility * implied_volatility) / 2) * time_to_expiry) /
     (implied_volatility * std::sqrt(time_to_expiry));

    double d2 = d1 - implied_volatility * std::sqrt(time_to_expiry);

    std::pair<double, double> d1d2;
    d1d2.first = d1;
    d1d2.second = d2;

    return d1d2;
    }

    double Pricer::black_scholes_call_price(const Stock& stock) {
        std::pair<double, double> d1d2 = black_scholes_primer(stock);
        double d1 = d1d2.first;
        double d2 = d1d2.second;

        double call_price = stock_price * norm_cdf(d1) - strike_price * 
        std::exp(-risk_free_rate * time_to_expiry) * norm_cdf(d2);

        return call_price;
    }

    double put_price = strike_price * std::exp(-risk_free_rate * time_to_expiry) * norm_cdf(-d2) - stock_price * norm_cdf(-d1);
}

    