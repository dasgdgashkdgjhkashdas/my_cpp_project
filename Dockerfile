# Этап сборки
FROM gcc:13 AS builder

RUN apt-get update && apt-get install -y cmake && apt-get clean

WORKDIR /app
COPY . .

RUN mkdir build && cd build && \
    cmake .. -DBUILD_TESTS=ON && \
    make -j$(nproc)

# Финальный образ
FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y ca-certificates && apt-get clean

WORKDIR /app

# Копируем приложение и тесты
COPY --from=builder /app/build/my_app .
COPY --from=builder /app/build/my_tests .

CMD ["./my_app"]