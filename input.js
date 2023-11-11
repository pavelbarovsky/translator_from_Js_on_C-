const PI = Math.PI;

function calculateArea(radius) {
  let squaredRadius = Math.pow(radius, 2);
  const circumference = 2 * PI * radius;

  if (circumference > 50) {
    let area = PI * squaredRadius;
    console.log(`The area is: ${area}`);

    for (let i = 0; i < 5; i++) {
      if (i % 2 === 0) {
        const halfRadius = radius / 2;
        let innerArea = PI * Math.pow(halfRadius, 2);

        while (innerArea > 10) {
          console.log(`Inner area is still greater than 10: ${innerArea}`);
          innerArea -= 5;
        }
      } else {
        let randomOffset = Math.random() * 10;
        let modifiedRadius = radius + randomOffset;

        const updatedArea = PI * Math.pow(modifiedRadius, 2);
        console.log(`Updated area for iteration ${i}: ${updatedArea}`);
      }
    }
  } else {
    console.log('Circumference is not greater than 50.');
  }
}

// Пример использования функции
calculateArea(8);
