package com.example.ThymeleafProject;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.MessageSource;
import org.springframework.context.annotation.Bean;
import org.springframework.context.support.ReloadableResourceBundleMessageSource;
import org.springframework.web.servlet.LocaleResolver;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import org.springframework.web.servlet.i18n.SessionLocaleResolver;
import java.util.Locale;
import org.apache.catalina.Context;
import org.apache.tomcat.util.descriptor.web.FilterDef;
import org.apache.tomcat.util.descriptor.web.FilterMap;
import org.springframework.boot.web.embedded.tomcat.TomcatServletWebServerFactory;
import org.springframework.boot.web.servlet.server.ServletWebServerFactory;
import org.springframework.web.filter.CharacterEncodingFilter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.ArrayList;
import java.util.List;


@SpringBootApplication
public class ThymeleafProjectApplication implements WebMvcConfigurer {

	public static void main(String[] args) {
		SpringApplication.run(ThymeleafProjectApplication.class, args);
	}

	@Bean
	public MessageSource messageSource() {
		ReloadableResourceBundleMessageSource messageSource = new ReloadableResourceBundleMessageSource();
		messageSource.setBasename("classpath:messages");
		messageSource.setDefaultEncoding("UTF-8");
		return messageSource;
	}

	@Bean
	public LocaleResolver localeResolver() {
		SessionLocaleResolver slr = new SessionLocaleResolver();
		slr.setDefaultLocale(new Locale("ru", "RU")); // Русский язык по умолчанию
		return slr;
	}

	@Bean
	public ServletWebServerFactory servletContainer() {
		TomcatServletWebServerFactory tomcat = new TomcatServletWebServerFactory() {
			@Override
			protected void postProcessContext(Context context) {
				FilterDef filterDef = new FilterDef();
				filterDef.setFilterName("setCharacterEncodingFilter");
				filterDef.setFilterClass(CharacterEncodingFilter.class.getName());
				filterDef.addInitParameter("encoding", "UTF-8");
				filterDef.addInitParameter("forceEncoding", "true");
				context.addFilterDef(filterDef);

				FilterMap filterMap = new FilterMap();
				filterMap.setFilterName("setCharacterEncodingFilter");
				filterMap.addURLPattern("/*");
				context.addFilterMap(filterMap);
			}
		};
		return tomcat;
	}

	@Configuration
	public class AppConfig {

		@Bean
		public List<DroneObj> drones() {
			return new ArrayList<>();
		}
	}
}
