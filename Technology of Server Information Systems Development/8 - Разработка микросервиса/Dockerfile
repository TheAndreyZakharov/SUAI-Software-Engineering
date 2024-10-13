FROM eclipse-temurin:17.0.9_9-jdk
RUN mkdir -p /usr/src/myapp
COPY target/ProjectKafka111.jar /usr/src/myapp
RUN mkdir -p /usr/src/myapp/target
COPY target/keystore.p12 /usr/src/myapp/target
WORKDIR /usr/src/myapp
ENTRYPOINT ["java","-jar","./ProjectKafka111.jar"]
