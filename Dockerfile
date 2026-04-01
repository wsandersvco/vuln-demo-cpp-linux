# Use specific version tag for reproducibility
FROM --platform=linux/amd64 gcc:13.2.0

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        openjdk-17-jdk \
        curl \
        ca-certificates \
        make \
        zip \ 
        crossbuild-essential-arm64 && \
    curl -fsS https://tools.veracode.com/veracode-cli/install | sh && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

WORKDIR /app

CMD ["bash"]
